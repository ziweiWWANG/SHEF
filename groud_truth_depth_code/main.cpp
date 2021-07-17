#include <iostream>
#include <vector>
#include <fstream>

#include "eigen3/Eigen/Dense"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/calib3d.hpp"
#include <opencv2/core/eigen.hpp>
#include <iomanip> 

#include "opencv2/highgui.hpp"


#ifndef CONFIG_FILE
#define CONFIG_FILE "unknown"
#endif


#define TEST_IMAGES false

using namespace std;
using namespace Eigen;
using namespace cv;

static constexpr int skipPixelsExponent = 0;
static constexpr int skipPixels = (int) pow(2, skipPixelsExponent);
// static constexpr int resx = 752 / skipPixels;
// static constexpr int resy = 480 / skipPixels;
static constexpr int resx = 2048 / skipPixels;
static constexpr int resy = 1536 / skipPixels;
static constexpr float rayEps = 0.009;
static constexpr float rayErrorLimit = 1.0 - rayEps*rayEps;

static const int counterStart = 1397;
static const int counterStep = 1; 
static const int counterEnd = 3000;

struct Pose {
    Matrix3f R;
    Vector3f x;
    long long t;

    bool operator<(const Pose& other) {
        return t < other.t;
    }
    bool operator<(const long long& tstamp) {
        return t < tstamp;
    }
};

Matrix<float, 3, Dynamic> readPointCloud(const string& fname);
int countLines(const string& fname);
float getDepthAtRay(const Matrix<float, 3, Dynamic>& cloud, const vector<float>& depths, const Vector3f& ray);
vector<Vector3f> makeCameraRays();
vector<float> makeDepthArray(const vector<Vector3f>& camRays, const vector<Vector3f>& goodCloudVec);
vector<Pose> readCameraPoses(const string& fname);
vector<Vector3f> filterCloud(const Matrix<float,3,Dynamic>& cloud, const vector<Vector3f>& camRays);

int main(int argc, char const *argv[])
{
    // cout << "Skipping this many pixels: " << skipPixels << endl;
    cout << "Reading the config file: " << CONFIG_FILE << endl;

    string cloudFname, camFname;
    ifstream configFile(CONFIG_FILE);
    getline(configFile, cloudFname);
    getline(configFile, camFname);

    cout << "Reading pointcloud" << endl;
    Matrix<float, 3, Dynamic> pcl = readPointCloud(cloudFname);

    cout << "Making camera rays" << endl;
    vector<Vector3f> camRays = makeCameraRays();

    cout << "Reading the camera poses" << endl;
    vector<Pose> camPoses = readCameraPoses(camFname);

    int counter = 1;

    for (const Pose& camPose : camPoses) {
        if (counter < counterStart) {
            counter += counterStep;
            continue;
        } else if (counter >= counterEnd) {
            break;
        }

        cout << "Camera Position" << endl;
        cout << camPose.x << endl;
        cout << "Processing Image " << counter << endl;

        // Transform the cloud to this pose
        Matrix<float, 3, Dynamic> bcl = camPose.R.transpose() * (pcl.colwise() - camPose.x );

        // Making a depth array
        vector<Vector3f> goodCloudVec = filterCloud(bcl, camRays);
        vector<float> depthArray = makeDepthArray(camRays, goodCloudVec);

        if(depthArray.size() == resx*resy) // check that the rows and cols match the size of your vector
        {
            Mat m = Mat(resy, resx, CV_32FC1); // initialize matrix of uchar of 1-channel where you will store vec data
            for (int r=0;r<resy;++r) {
            for (int c=0;c<resx;++c) {
                m.at<float>(r,c) = depthArray[r+c*resy];
            }   
            }
            
            // Write UC8 images for testing
            if (TEST_IMAGES) {
                m = m * 255;
                m.convertTo(m, CV_16UC1);
                stringstream output_fname;
                output_fname << "depths/depth_" << counter << ".png";
                cout << output_fname.str() << endl;
                imwrite(output_fname.str(), m);
            } else {
                // Write exr for real output
                stringstream output_fname;
                output_fname << "depths/depth_" << counter << ".exr";
                imwrite(output_fname.str(), m);
                
                // Write png for real output
                m = m * 255;
                m.convertTo(m, CV_16UC1);
                stringstream output_fname_png;
                output_fname_png << "depths/depth_" << counter << ".png";
                cout << output_fname_png.str() << endl;
                imwrite(output_fname_png.str(), m);
            }
        }
        // string = "image"+to_string(counter)+".pfm";
        counter += counterStep;
    }
    return 0;
}

Matrix<float, 3, Dynamic> readPointCloud(const string& fname) {
    // Count the lines in the file
    const int lineCount = countLines(fname);
    const int entryCount = lineCount - 2;
    Matrix<float, 3, Dynamic> result = MatrixXf(3, entryCount);

    // Read the input file
    ifstream cloudFile = ifstream(fname);
    int counter = 0;
    string line;
    while (getline(cloudFile, line)) {
        ++counter;
        if (counter < 3) continue; // Skip the first couple of lines
        
        istringstream iss(line);
        string entry;
        for (int i=0; i<3; ++i) {
            iss >> entry;
            result(i,counter-3) = stof(entry);
        }   
    }
    cloudFile.close();
    return result;
}

int countLines(const string& fname) {
    ifstream inFile = ifstream(fname);
    int counter = 0;
    string line;
    while (getline(inFile, line)) {
        ++counter;
    }
    inFile.close();
    return counter;
}

float getDepthAtRay(const Matrix<float, 3, Dynamic>& cloud, const vector<float>& depths, const Vector3f& ray) {
    Matrix<float, 1, Dynamic> scores = ray.transpose() * cloud;

    float depth = 1000;
    for (int i=0; i<scores.cols(); ++i) {
        if ((scores[i] > rayErrorLimit) && depths[i] < depth)
            depth = depths[i];
    }
    if (depth > 100) depth = 0.0;

    return depth;
}

vector<Vector3f> filterCloud(const Matrix<float,3,Dynamic>& cloud, const vector<Vector3f>& camRays) {
    // Get camrays min and max
    float minx = 1e8, maxx = -1e8, miny = 1e8, maxy = -1e8;
    for (const Vector3f& ray : camRays) {
        if (ray.x() < minx) minx = ray.x();
        else if (ray.x() > maxx) maxx = ray.x();
        if (ray.y() < miny) miny = ray.y();
        else if (ray.y() > maxy) maxy = ray.y();
    }

    // Filter the cloud
    vector<Vector3f> goodCloudVec;
    for (int i=0; i<cloud.cols();++i) {
        if (
            (cloud(0,i) >= (minx-30*rayEps)*cloud(2,i)) &&
            (cloud(0,i) <= (maxx+30*rayEps)*cloud(2,i)) &&
            (cloud(1,i) >= (miny-30*rayEps)*cloud(2,i)) &&
            (cloud(1,i) <= (maxy+30*rayEps)*cloud(2,i)) &&
            (cloud(2,i) > 0)
        ) {
            goodCloudVec.emplace_back(cloud.block<3,1>(0,i));
        }
    }
    return goodCloudVec;
}

vector<Vector3f> makeCameraRays() {

    // Make initial rays
    vector<Point2f> pixelRays(resx*resy);
    for (int x=0;x<resx;++x){
    for (int y=0;y<resy;++y){
        pixelRays[x*resy+y] = Point2f(x,y);
    }
    }

    float KData[9] = {1301.270298, 0, 1006.654444, 0, 1301.270298, 771.105734, 0,       0,       1};
    Mat K0 = Mat(3,3, CV_32FC1, KData);
    K0 = K0 / skipPixels;
    K0.at<float>(2,2) = 1.0;
    const Mat K = K0;
    float distData[4] = {-0.222015, 0.118734, 0, 0}; //k1 k2 p1 p2
    const Mat dist = Mat(1,4, CV_32FC1, distData);
    const Mat nodist = Mat(1,4, CV_32FC1, {0,0,0,0});

    // undistort the rays
    vector<Point2f> normalRaysCV;
    undistortPoints(pixelRays, normalRaysCV, K, dist);

    // Turn into eigen
    auto rayLambda = [](const Point2f& nray) {
        Vector3f ray;
        ray << nray.x, nray.y, 1.0;
        ray.normalize();
        return ray;
    };
    vector<Vector3f> cameraRays(normalRaysCV.size());
    transform(normalRaysCV.begin(), normalRaysCV.end(), cameraRays.begin(), rayLambda);
    return cameraRays;
}

vector<float> makeDepthArray(const vector<Vector3f>& camRays, const vector<Vector3f>& goodCloudVec) {
    Matrix<float, 3, Dynamic> goodCloud = MatrixXf(3, goodCloudVec.size());
    vector<float> depths(goodCloudVec.size());
    for (int i=0; i<goodCloudVec.size();++i) {
        depths[i] = goodCloudVec[i].norm();
        goodCloud.block<3,1>(0,i) = goodCloudVec[i].normalized();
    }

    auto depthLambda = [&goodCloud, &depths] (const Vector3f& ray) { return getDepthAtRay(goodCloud, depths, ray); };
    vector<float> depthArray(camRays.size());
    transform(camRays.begin(), camRays.end(), depthArray.begin(), depthLambda);
    return depthArray;
}

vector<Pose> readCameraPoses(const string& fname) {
    const int numPoses = countLines(fname);
    vector<Pose> poses;

    // Read the input file
    ifstream poseFile = ifstream(fname);
    int counter = 0;
    string line;
    while (getline(poseFile, line)) {
        ++counter;        
        istringstream iss(line);
        string entry;
        vector<string> lineData;
        while (getline(iss, entry, ' ')) {
            lineData.emplace_back(entry);
        }

        // Parse the line data
        Pose camPose;
        camPose.x << stof(lineData[1]), stof(lineData[2]), stof(lineData[3]);    
        Mat Rt = (Mat_<double>(3,3) <<
               stof(lineData[4]), stof(lineData[5]), stof(lineData[6]),
               stof(lineData[7]), stof(lineData[8]), stof(lineData[9]),
               stof(lineData[10]), stof(lineData[11]), stof(lineData[12])
               );
        Eigen::MatrixXf eigen_mat(3, 3);
        cv::cv2eigen(Rt, eigen_mat);
        camPose.R = eigen_mat;
        poses.emplace_back(camPose);

    }
    poseFile.close();
    return poses;
}





