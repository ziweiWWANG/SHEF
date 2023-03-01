function output = remove_outlier_disparity(input,sz)
    %% Remove 0 disparity pixels
    output = input; 
    output(output<1) = NaN;
    tmpOut = output;
    
    %% Remove outlier
    for r = 1:size(input,1)
        for c = 1:size(input,2)
            ind = sub2ind(size(input), min(max([r-sz:r+sz], 1), size(input,1)),  min(max([c-sz:c+sz], 1), size(input,2)));
            tmp = tmpOut(ind); 
            tmp(isnan(tmp)) = [];
            if numel(tmp)<4
                tmpOut(r,c) = 0;
            elseif abs(tmpOut(r,c)-median(tmp))/median(tmp)>1/3 || abs(tmpOut(r,c)-median(tmp))>10
                tmpOut(r,c) = 0;
            end
        end
    end
    output = tmpOut; 
end