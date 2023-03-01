# Stereo Hybrid Event-Frame (SHEF) Cameras for 3D Perception
<p align="center">
  <a href="https://www.youtube.com/watch?v=Azu7rJSPGNc">
    <img src="figures/video_thumbnail.png" alt="Stereo Hybrid Event-Frame (SHEF) Cameras for 3D Perception" width="500"/>
  </a>
</p>



Ziwei Wang, Liyuan Pan, Yonhon Ng, Zheyu Zhuang and Robert Mahony

The paper was accepted by the 2021 IEEE/RSJ International Conference on Intelligent Robots and Systems (IROS 2021) in Prague, Czech Republic.

[[Paper](https://ieeexplore.ieee.org/abstract/document/9636312)]
[[ArXiv](https://arxiv.org/abs/2110.04988)]


## Citation 
If you use or discuss our SHEF algorithm, or use the dataset, please cite our paper as follows:
<pre>
@inproceedings{wang2021stereo,
  title={Stereo Hybrid Event-Frame (SHEF) Cameras for 3D Perception},
  author={Wang, Ziwei and Pan, Liyuan and Ng, Yonhon and Zhuang, Zheyu and Mahony, Robert},
  booktitle={2021 IEEE/RSJ International Conference on Intelligent Robots and Systems (IROS)},
  year={2021},
  organization={IEEE}
}
</pre>



## [Download Data](https://anu365-my.sharepoint.com/:f:/g/personal/u6456661_anu_edu_au/EuotzBGRLk1AhfOe9LlZuSQBVtis9MH86vz1DQgt8hzQPA?e=jhRg1h) 

### [stereo_event_frame_raw_data](https://anu365-my.sharepoint.com/:f:/g/personal/u6456661_anu_edu_au/Ej1WwLyZqAFFtf-QZxvE8tYBkJkL-IYwUyzE1NDFpsI4aA?e=0vZNak)

Three scenarios: [`picnic`](https://anu365-my.sharepoint.com/:f:/g/personal/u6456661_anu_edu_au/Enz2dm5fBxlFkimada8OUnwB5QcI5SdzwTb4MmDTT1AY7g?e=9HKLyL), [`complex boxes`](https://anu365-my.sharepoint.com/:f:/g/personal/u6456661_anu_edu_au/EtcIck30nRBBq9n8Ozne-WEBeAf1rM6L9ka42TnNMBO1FA?e=GqjZMd), and [`simple boxes`](https://anu365-my.sharepoint.com/:f:/g/personal/u6456661_anu_edu_au/Em7JHxte1uFOpzKPeuCUyW0BmFdb_adsgNOBVHdxxN4JQg?e=fchosA).
Each scenario includes at least 6 sequences with different camera speeds and lighting conditions.


|                      | From FLIR RGB camera | From Prophesee event camera | Description                                                                                             |
|----------------------|----------------------|-----------------------------|---------------------------------------------------------------------------------------------------------| 
| `intensity_images`  | yes                     | no                          |Synchronised intensity images from FLIR RGB camera |
| `images_ts.txt`     | no                      | yes                         |Timestamps of the ynchronised intensity images. We synchronise the two cameras by sending a trigger signal from the FLIR RGB camera to the event camera. |
| `log_td.dat`        | no                      | yes                         |Event data, includes event x, y, ts, p |                                             


### [processed depth ground truth examples](https://anu365-my.sharepoint.com/:f:/g/personal/u6456661_anu_edu_au/EqtwBFaIBp9FhJRtIvqK6scB0esgEt9wUZoQ5u3Oa82DBA?e=WRvCSX)


### [parameters for each sequence](https://docs.google.com/spreadsheets/d/1so2S-R-0OyHtPx6rzRnHimwNJFnQP-UNSiHOV1cqRFM/edit?usp=sharing)


### [stereo hybrid event-frame calibration data](https://anu365-my.sharepoint.com/:u:/g/personal/u6456661_anu_edu_au/EYYaSawiB6hPl2HC03Ig4RgBOq4RsrNylGyl2SdoYqdMTw?e=nAwUdt)

### [point cloud](https://anu365-my.sharepoint.com/:f:/g/personal/u6456661_anu_edu_au/Egwt0pIEaJ9AqrHuImMSupgBJ7WmxOEFV5KCtJreVsoH_g?e=pryE01)


### [UR5 robot arm pose](https://anu365-my.sharepoint.com/:f:/g/personal/u6456661_anu_edu_au/ErQDYXOfZ5FKoziHVxyqusgBN4JwASJUh8ue_Hsah9Aclw?e=IREwdD)

## Run Our Baseline Disparity Algorithm
Run [run_disparity.m](https://github.com/ziweiWWANG/SHEF/baseline_disparity_code/run_disparity.m).
It will load event-frame pairs from [baseline_disparity_code/data/event_edge](https://github.com/ziweiWWANG/SHEF/baseline_disparity_code/include/data/event_edge) and [baseline_disparity_code/data/frame_edge](https://github.com/ziweiWWANG/SHEF/baseline_disparity_code/include/data/frame_edge).


## Evaluation
Enter folder [baseline_disparity_code/include](https://github.com/ziweiWWANG/SHEF/baseline_disparity_code/include) and run [evaluation.m](https://github.com/ziweiWWANG/SHEF/baseline_disparity_code/include/evaluation.m).
It will load estimated depth from [baseline_disparity_code/data/Dp](https://github.com/ziweiWWANG/SHEF/baseline_disparity_code/include/data/Dp) and ground truth depth from [baseline_disparity_code/data/gt](https://github.com/ziweiWWANG/SHEF/baseline_disparity_code/include/data/gt), and display the average `bad-p`, `RMSE` and `inlier ratio` performance.

## Notes: 
1. Events are decompressed from `.raw` to `.dat` format. To convert raw data to `.dat` or `.csv` format, we used the Prophesee tools in [Prophesee_tools](https://anu365-my.sharepoint.com/:f:/g/personal/u6456661_anu_edu_au/EgqGLGx573ZOnbobjQZMT1YBO-7eSgtCtZivu72CxdMz8Q?e=hceb06)
You can also install the last Prophesee software version follow the instructions on the [website](https://support.prophesee.ai/portal/en/kb/articles/linux-software#Prerequisites)
If you need, you can find all tools in `usr/share/prophesee_driver/samples/` or `usr/share/metavision/sdk/driver/samples/`, depending on what version you are using.

2. You can use the provided code to generate depth groud truth from camera position and point cloud. Or you can download the example depth ground truth images from [processed depth ground truth examples](https://anu365-my.sharepoint.com/:f:/g/personal/u6456661_anu_edu_au/EqtwBFaIBp9FhJRtIvqK6scB0esgEt9wUZoQ5u3Oa82DBA?e=WRvCSX).

3. For academic use only. Should you have any questions regarding this paper or datasets, please contact [ziwei.wang1@anu.edu.au](ziwei.wang1@anu.edu.au)
