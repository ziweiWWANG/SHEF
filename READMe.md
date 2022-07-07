# Stereo Hybrid Event-Frame (SHEF) Cameras for 3D Perception
<p align="center">
  <a href="https://www.youtube.com/watch?v=Azu7rJSPGNc">
    <img src="figures/video_thumbnail.png" alt="Stereo Hybrid Event-Frame (SHEF) Cameras for 3D Perception" width="500"/>
  </a>
</p>

## For academic use only.




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



## Data 

### Download

#### [processed stereo event-frame dataset](https://anu365-my.sharepoint.com/:f:/g/personal/u6456661_anu_edu_au/Ej1WwLyZqAFFtf-QZxvE8tYBkJkL-IYwUyzE1NDFpsI4aA?e=7qxuuW)

#### [parameters for each sequence](https://docs.google.com/spreadsheets/d/1so2S-R-0OyHtPx6rzRnHimwNJFnQP-UNSiHOV1cqRFM/edit?usp=sharing)

#### [stereo hybrid event-frame calibration data](https://anu365-my.sharepoint.com/:f:/g/personal/u6456661_anu_edu_au/EhBpyboR6vFMpVS542vnepMBDW5pCX2Ydu6-K2cx4IAO4w?e=lahziB)

#### [point cloud](https://anu365-my.sharepoint.com/:f:/g/personal/u6456661_anu_edu_au/Egwt0pIEaJ9AqrHuImMSupgBJ7WmxOEFV5KCtJreVsoH_g?e=RKmKOp)

#### [UR5 robot arm pose](https://anu365-my.sharepoint.com/:f:/g/personal/u6456661_anu_edu_au/ErQDYXOfZ5FKoziHVxyqusgBN4JwASJUh8ue_Hsah9Aclw?e=GfjUQa)

#### [Processed Depth Ground Truth Examples](https://anu365-my.sharepoint.com/:f:/g/personal/u6456661_anu_edu_au/EqtwBFaIBp9FhJRtIvqK6scB0esgEt9wUZoQ5u3Oa82DBA?e=NAZeoe)

### Events Image Raw Data:
Three scenarios: picnic, complex boxes, and simple boxes.
Each scenario includes at least 6 sequences with different camera speeds and lighting conditions.


|                      | From FLIR RGB camera | From Prophesee event camera | Description                                                                                             |
|----------------------|----------------------|-----------------------------|---------------------------------------------------------------------------------------------------------| 
| `Intensity images`  | yes                     | no                          |Synchronised intensity images from FLIR RGB camera |
| `images_ts.txt`     | no                      | yes                         |Timestamps of the ynchronised intensity images. We synchronise the two cameras by sending a trigger signal from the FLIR RGB camera to the event camera. |
| `log_td.dat`        | no                      | yes                         |Event data, includes event x, y, ts, p |                                             

#### Notes: 
1. Events are decompressed from `.raw` to `.dat` format. To convert raw data to `.dat` or `.csv` format, we used the Prophesee tools in [Prophesee_tools](https://anu365-my.sharepoint.com/:f:/g/personal/u6456661_anu_edu_au/EgqGLGx573ZOnbobjQZMT1YBO-7eSgtCtZivu72CxdMz8Q?e=hceb06)
You can also install the last Prophesee software version follow the instructions on the [website](https://support.prophesee.ai/portal/en/kb/articles/linux-software#Prerequisites)
If you need, you can find all tools in `usr/share/prophesee_driver/samples/` or `usr/share/metavision/sdk/driver/samples/`, depending on what version you are using.

2. You can use the provided code to generate depth groud truth from camera position and point cloud. Or you can download the example depth ground truth images from [Processed Depth Ground Truth Examples](https://anu365-my.sharepoint.com/:f:/g/personal/u6456661_anu_edu_au/EqtwBFaIBp9FhJRtIvqK6scB0esgEt9wUZoQ5u3Oa82DBA?e=NAZeoe).


## Notes 
1. Should you have any questions regarding this paper or datasets, please contact ziwei.wang1@anu.edu.au
