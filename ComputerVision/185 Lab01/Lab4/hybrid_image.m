function img_merged = hybrid_image(img1, img2, ratio)
    [low_pass_img1, high_pass_img1] = separate_frequency(img1, ratio);
    [low_pass_img2, high_pass_img2] = separate_frequency(img2, ratio);
    
    %canvas(size(img1, 1), size(img1,2)) = img_merged;
    img_merged = (high_pass_img1 + low_pass_img2)/2;
    %img_merged = (high_pass_img2 + low_pass_img1)/2;
end