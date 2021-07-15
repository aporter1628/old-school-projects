function [low_pass_img, high_pass_img] = separate_frequency(img, ratio)
    frequency_map = fft2(img);
    frequency_map_shifted = fftshift(frequency_map);

    h = size(img,2);
    w = size(img, 1);
    y1 = h/2 - (ratio*h)/2;
    y2 = h/2 + (ratio*h)/2;
    x1 = w/2 - (ratio*w)/2;
    x2 = w/2 + (ratio*w)/2;

    mask = zeros(size(img));
    mask(x1 : x2, y1 : y2, :) = 1;

    low_frequency_map_shifted = frequency_map_shifted .* mask;
    high_frequency_map_shifted = frequency_map_shifted .* (1 - mask);

    low_frequency_map = ifftshift(low_frequency_map_shifted);
    high_frequency_map = ifftshift(high_frequency_map_shifted);

    low_pass_img = real(ifft2(low_frequency_map));
    high_pass_img = real(ifft2(high_frequency_map));

end
