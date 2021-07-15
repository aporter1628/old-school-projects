img = im2double(imread('lena.jpg'));
frequency_map = fft2(img);
%figure, imshow(log(abs(frequency_map) + 1), [])

img = im2double(imread('lena.jpg'));
ratio = 0.2;
[low_pass_img, high_pass_img] = separate_frequency(img, ratio);

%figure, imshow(low_pass_img)
%figure, imshow(high_pass_img + 0.5)
imwrite(low_pass_img, 'lena_low_pass.jpg');
imwrite(high_pass_img + 0.5, 'lena_high_pass.jpg');

%Task2
name1 = 'marilyn.jpg';
name2 = 'einstein.jpg';
img1 = im2double(imread(name1));
img2 = im2double(imread(name2));
ratio = 0.25;
img_merged = hybrid_image(img1, img2, ratio);
figure, imshow(img_merged);

