%#1
img = im2double(imread('lena.jpg'));
%% Sobel filter
%H = [1, 2, 1; 0, 0, 0; -1, -2, -1]; % horizontal edge
H = [1, 0, -1; 2, 0, -2; 1, 0, -1]; % vertical edge
img_sobel = sobel_filter(img, H);
figure, imshow(img_sobel);
%imwrite(img_sobel, 'sobel_h.jpg');

%#3
%% Gaussian filter
%hsize = 5; sigma = 2;
hsize = 9; sigma = 4;
img_gaussian = gaussian_filter(img, hsize, sigma);
figure, imshow(img_gaussian);
%imwrite(img_gaussian, 'gaussian_5.jpg');
H = fspecial('gaussian', hsize, sigma);
I2 = imfilter(img_gaussian, H);
figure, imshow(I2);