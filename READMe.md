# For academic use only.


## Stereo Hybrid Event-Frame Camera Dataset for 3D Perception

⋅⋅* Ziwei Wang, Yonhon Ng, Liyuan Pan, Zheyu Zhuang and Robert Mahony

⋅⋅* The paper was accepted by the 2021 IEEE/RSJ International Conference on Intelligent Robots and Systems (IROS 2021) in Prague, Czech Republic.
   
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
| log.raw              | no                   | yes                         | Event data, includes event x, y, ts, p                                                                  |
| log_trigger.dat      | yes                  | yes                         | We synchronise the two cameras by sending a trigger signal from the FLIR RGB camera to the event camera |
| log_id.txt           | no                   | yes                         | Event camera information                                                                                |
| log.bias             | no                   | yes                         | Event camera bias                                                                                       |



