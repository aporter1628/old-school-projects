I1 = imread('01.jpg');
I2 = zeros(300, 400, 3, 'uint8');
%I2 = I1;

%get the origin x0, y0
x0 = 200;
y0 = 150;


%apply the formula to each pixel in I1 and map to I2
for y = 1:size(I1, 1)
    for x = 1:size(I1, 2)
        x2 = round(cosd(45) * (x - x0) + sind(45) * (y - y0) + x0);
        y2 = round(-sind(45) * (x - x0) + cosd(45) * (y - y0) + y0);
        if(y2 <= 300 && y2 > 0 && x2 <= 400 && x2 > 0)
            I2(y2, x2, :) = I1(y, x, :);
        end  
    end
end

figure; imshow(I2);
imwrite(I2, 'rotate_0.jpg');


%task 2
I3 = zeros(300, 400, 3, 'uint8');

%apply the formula to each pixel in I1 and map to I3
for y2 = 1:size(I2, 1)
    for x2 = 1:size(I2, 2)
        x = round(cosd(45) * (x2 - x0) + -sind(45) * (y2 - y0) + x0);
        y = round(sind(45) * (x2 - x0) + cosd(45) * (y2 - y0) + y0);
        if(y <= 300 && y > 0 && x <= 400 && x > 0)
            I3(y2, x2, :) = I1(y, x, :);
        end  
    end
end

figure; imshow(I3)
imwrite(I2, 'rotate_1.jpg');

%task 3
img = im2double(imread('lena_noisy.jpg'));
%Median filter
patch_size = [3, 3];
% patch_size = [5, 5];
%img_median = median_filter(img, patch_size);
%imwrite(img_median, ‘median.jpg’);




