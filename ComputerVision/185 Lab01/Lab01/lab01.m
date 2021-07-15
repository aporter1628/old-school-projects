%#1
im = imread('01.jpg')
im(:,:,2) = 0;
figure; imshow(im)
%imwrite(im, green.jpg);

%#2
im2 = imread('01.jpg')
im2 = 0.2989 * im2(:,:,1) + 0.5870 * im2(:,:,2) + 0.1140 * im2(:,:,3);
figure; imshow(im2)

%#3
im3 = imread('01.jpg');
I = imrotate(im3, 90);
figure; imshow(I)

%#4 upper left (30,100) lower right (270, 300)
I2 = im3(30:100, 270:300)
figure; imshow(I2)

%#5
I3 = flip(im3, 2)
figure; imshow(I3)

%#6
im1 = imread('01.jpg')
canvas = zeros(300*2 + 10, 400*2 + 10, 3, 'uint8');
canvas(1:300, 1:400, :) = im1;
im2 = imread('02.jpg')
canvas(1:300, 411:810, :) = im2;
im3 = imread('03.jpg')
canvas(311:610, 1:400, :) = im3;
im4 = imread('04.jpg')
canvas(311:610, 411:810, :) = im4;
figure; imshow(canvas)

%#7
im5 = imread('05.jpg');
%sz = size(im5)
im5 = im5(:);
im6 = imread('06.jpg');
im6 = im6(:);
im7 = (im5 + im6) / 2;
im7 = reshape(im7, 375, 1242, 3);
figure; imshow(im7)
