img = im2double(imread('lena.jpg'));
sigma = 2.0;
hsize = 7;
scale = 5;
%% Gaussian Pyramid
I = img;
for s = 1 : scale
    % Gaussian filter
    h = fspecial('gaussian', hsize, sigma);
    I = imfilter(I, h);
    %I = imgaussfilt(img);
    % Save or show image
    %figure; imshow(I);
    imwrite(I, sprintf('Gaussian_scale%d.jpg', s));
    % Down-sampling
    I = imresize(I, 0.5);
end

I = img;
%% Laplacian Pyramid
for s = 1 : scale
    I2 = I;
    % Gaussian filtering
    h = fspecial('gaussian', hsize, sigma);
    I = imfilter(I, h);
    % Laplacian filtering
    I = I2 - I;
    % Save or show image
    %figure; imshow(I + 0.5);
    imwrite(I + 0.5, sprintf('Laplacian_scale%d.jpg', s));
    % Down-sampling
    I = imresize(I, 0.5);
end

%name = 'einstein1';
name = 'einstein2';
img = im2double(imread(sprintf('%s.jpg', name)));
template = im2double(imread('template.jpg'));
%% SSD
threshold = 35;
[output, match] = template_matching_SSD(img, template, threshold);
figure, imshow(output ./ max(output(:))); title('SSD output');
figure, imshow(match); title('SSD match');
imwrite(output ./ max(output(:)), sprintf('%s_ssd_output.jpg', name));
imwrite(match, sprintf('%s_ssd_match.jpg', name));

%% Normalized Cross-Correlation
threshold = 0.7;
[output, match] = template_matching_normcorr(img, template, threshold);
%figure, imshow(output ./ max(output(:))); title('NormCorr output');
%figure, imshow(match); title('NormCorr match');
imwrite(output ./ max(output(:)), sprintf('%s_normcorr_output.jpg', name));
imwrite(match, sprintf('%s_normcorr_match.jpg', name));

