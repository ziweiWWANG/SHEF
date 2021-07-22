# For academic use only.


## Stereo Hybrid Event-Frame (SHEF) Cameras for 3D Perception

Ziwei Wang, Liyuan Pan, Yonhon Ng, Zheyu Zhuang and Robert Mahony

The paper was accepted by the 2021 IEEE/RSJ International Conference on Intelligent Robots and Systems (IROS 2021) in Prague, Czech Republic.
   
## Publications 
Coming soon

## IROS-video
Coming soon

## Notes 
1. If you have any questions regarding this code and the corresponding results, please contact ziwei.wang1@anu.edu.au

## Data 
### Events Image Raw Data:
Three scenarios: picnic, complex boxes, and simple boxes.
Each scenario includes at least 6 sequences with different camera speeds and lighting conditions.

|                      | From FLIR RGB camera | From Prophesee event camera | Description                                                                                             |
|----------------------|----------------------|-----------------------------|---------------------------------------------------------------------------------------------------------|
| raw intensity images | yes                  | no                          | Raw intensity images from FLIR RGB camera                                                               |
| log.raw              | no                   | yes                         | Raw event data, includes event x, y, ts, p, external FLIR camera trigger. Use [Prophesee_tools](https://anu365-my.sharepoint.com/:f:/g/personal/u6456661_anu_edu_au/EgqGLGx573ZOnbobjQZMT1YBO-7eSgtCtZivu72CxdMz8Q?e=Vf6goH) to convert to .dat or .csv                                                          |
| log_id.txt           | no                   | yes                         | Event camera information                                                                                |
| log.bias             | no                   | yes                         | Event camera bias                                                                                       |

#### Notes: 
Events are compressed in raw format. To convert raw data to .dat or .csv format, use the Prophesee tools in [Prophesee_tools](https://anu365-my.sharepoint.com/:f:/g/personal/u6456661_anu_edu_au/EgqGLGx573ZOnbobjQZMT1YBO-7eSgtCtZivu72CxdMz8Q?e=hceb06)
You can also install the last Prophesee software version follow the instructions on the [website](https://support.prophesee.ai/portal/en/kb/articles/linux-software#Prerequisites)
In this case, you can find all tools in /usr/share/prophesee_driver/samples or /usr/share/metavision/sdk/driver/samples, depending on what version you are using.

e.g.

To extract event dat files from log.raw:
./metavision_raw_to_dat -i log.raw --cd --em

To extract external FLIR camera trigger dat files from log.raw:
./metavision_raw_to_dat -i log.raw --trigger

|                      | From FLIR RGB camera | From Prophesee event camera | Description                                                                                             |
|----------------------|----------------------|-----------------------------|---------------------------------------------------------------------------------------------------------|       
| log_td.dat        | yes                     | No                          |Event data, includes event x, y, ts, p |                                             
| log_trigger.dat   | yes                     | yes                         |We synchronise the two cameras by sending a trigger signal from the FLIR RGB camera to the event camera. This is the external FLIR camera trigger signal file.|


To synchronise the two cameras by using log_trigger.dat:
1. Find the first raw image that has obvious exposure (intensity) changes.
2. Find its corresponding exposure change in log_trigger.dat. 
3. Compute image timestamp offset.

#### [Raw dataset](https://anu365-my.sharepoint.com/:f:/g/personal/u6456661_anu_edu_au/Ep_N2D67rfZDv9Ps9D7LOjMBpU7mIChHIQBLkW1dKbcnug?e=q2tGXu)

#### [Parameters for each sequence](https://docs.google.com/spreadsheets/d/1so2S-R-0OyHtPx6rzRnHimwNJFnQP-UNSiHOV1cqRFM/edit?usp=sharing)

#### [Stereo hybrid event-frame calibration data](https://anu365-my.sharepoint.com/:f:/g/personal/u6456661_anu_edu_au/EhBpyboR6vFMpVS542vnepMBDW5pCX2Ydu6-K2cx4IAO4w?e=lahziB)

#### [Point cloud](https://anu365-my.sharepoint.com/:f:/g/personal/u6456661_anu_edu_au/Egwt0pIEaJ9AqrHuImMSupgBJ7WmxOEFV5KCtJreVsoH_g?e=RKmKOp)

#### [UR5 robot arm pose](https://anu365-my.sharepoint.com/:f:/g/personal/u6456661_anu_edu_au/ErQDYXOfZ5FKoziHVxyqusgBN4JwASJUh8ue_Hsah9Aclw?e=GfjUQa)
