close all; clear;
folderName = '../data';
bad_p_num_Dp = 0;
p_num_Dp = 0;
inlier_num_Dp = [0,0,0];
total_inlier_num_Dp = 0;
rmse_dis_Dp = 0;

result_all = dir(sprintf([folderName '/Dp/*.pfm'])); 
result_num = size(result_all,1); 
gt_all = dir(sprintf([folderName '/gt/*.pfm'])); 
gt_num = size(gt_all,1); 
eval_num = min(result_num,gt_num);
for id = 1:eval_num
    % Load data and ground truth
    gt = read_pfm(sprintf([folderName '/gt/' result_all(id).name]));
    dis_Dp = read_pfm(sprintf([folderName '/Dp/' result_all(id).name]));
    Dp_thresh = remove_outlier_disparity(dis_Dp, 40); 
    Dp_thresh(isnan(Dp_thresh))=0;
    dis_Dp = Dp_thresh;
    
    % Do not evaluate on occlusion part for all methods
    dis_Dp(:,1:50) = 0;
    dis_Dp(:,620:end) = 0;
    mask = dis_Dp(:) == 0;
    
    err_dis = (dis_Dp(:)-gt(:)); err_dis(mask)=[];
    err_dis = abs(err_dis);
    
    % RMSE
    rmse_dis_Dp = rmse_dis_Dp + sqrt(mean2(err_dis.*err_dis));
    
    % Bad-p
    bad_p_num_Dp = bad_p_num_Dp + numel(find(err_dis>5));
    p_num_Dp = p_num_Dp + numel(err_dis);   
    
    % Inlier ratio
    gt = gt(:);
    dis_Dp = dis_Dp(:);
    gt(mask)=[]; 
    dis_Dp(mask)=[];
    comp = max(dis_Dp./gt,gt./dis_Dp);
    total_inlier_num_Dp = total_inlier_num_Dp + numel(gt);
    for i = 1:3
        inlier_num_Dp(i) = inlier_num_Dp(i) + numel(find(comp<1.25^(i)));  
    end
end
fprintf('Average bad-p Dp = %f\n', bad_p_num_Dp/p_num_Dp)
fprintf('Average RMSE Dp = %f\n', rmse_dis_Dp/eval_num)
fprintf('Average inlier ratio Dp: delta1 = %f, delta2 = %f, delta3 = %f\n', inlier_num_Dp(1)/total_inlier_num_Dp,inlier_num_Dp(2)/total_inlier_num_Dp,inlier_num_Dp(3)/total_inlier_num_Dp)    