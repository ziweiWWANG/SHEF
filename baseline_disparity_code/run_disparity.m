close all
clear
padsize = 120;
patch_size = 120;
windows = 120;
py_level = 5;
outlier_threshold = 50;
folderName = './data';
addpath('./include/export_fig')
addpath('./include')
start_id = 1;
end_id = 147;

if ~exist([folderName '/Dp'], 'dir')
   mkdir([folderName '/Dp'])
end
for imgID = start_id:end_id
    raw_add = sprintf([folderName '/frame_edge/%d.png'],imgID);
    hf_add = sprintf([folderName '/event_edge/%d.png'],imgID);
    J1 = imread(raw_add);
    J1 = double(J1);
    J2 = imread(hf_add);
    J2 = double(J2);
    
    %% Compute disparity
    X = sprintf('Computing Dp_%d ...',imgID);
    disp(X)
    [Dp,Ds] = estimatedisp(J1,J2,padsize,patch_size,windows,py_level);
    
    %% Remove outliers
    Dp_thresh = remove_outlier_disparity(Dp, outlier_threshold); 
    Dp_thresh(isnan(Dp_thresh))=0;

    %% Save Dp
    figure; imagesc(Dp_thresh,[0, 80])
    set(gca,'xtick',[],'ytick',[]);
    set(gcf,'OuterPosition', [0, 0.04, 640, 480]);
    set(gcf,'Color','white'); 
    write_pfm(Dp_thresh,sprintf([folderName '/Dp/%d.pfm'],imgID));
    export_fig(sprintf([folderName '/Dp/Dp_%d.png'],imgID))
    close all
end