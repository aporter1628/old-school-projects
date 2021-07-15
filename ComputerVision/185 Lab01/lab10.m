%% Load input images
%name = 'army';
%name = 'backyard';
 name = 'mequon';
%img1 = im2double(imread(fullfile('data', name, 'frame10.png')));
%img2 = im2double(imread(fullfile('data', name, 'frame11.png')));
img1 = im2double(imread(sprintf('%sFrame10.png', name)));
img2 = im2double(imread(sprintf('%sFrame11.png', name)));

%% parameters
window_size = 45;
k = 4; % number of iterations

w = floor(window_size/2);
shift = w + 10;


%% convert to gray-scale
I1 = rgb2gray(img1);
I2 = rgb2gray(img2);

%% compute gradients
Ix_m = imfilter(I1, [1 -1;  1 -1], 'replicate');
Iy_m = imfilter(I1, [1  1; -1 -1], 'replicate');


%% compute optical flow
u = zeros(size(I1));
v = zeros(size(I1));

u_next = zeros(size(I1));
v_next = zeros(size(I1));

for t = 1:k
    for i = 1 + shift : size(Ix_m, 1) - shift
        for j = 1 + shift : size(Ix_m, 2) - shift

            %% extract Ix, Iy, It from local window
            Ix = Ix_m(i-w:i+w, j-w:j+w);
            Iy = Iy_m(i-w:i+w, j-w:j+w);
            i2 = round(i + v(i,j));
            j2 = round(j + u(i,j));
            
            %% convert Ix, Iy, It to vectors
            It = I1(i-w:i+w, j-w:j+w) - I2(i2-w:i2+w, j2-w:j2+w);
            
            %% construct matrix A and vector b
            A = [Ix(:), Iy(:)];
            b = -It(:);
            
            %% solve A x = b
            x = A \ b;
            
            u_next(i, j) = x(1);
            v_next(i, j) = x(2);
            
        end
    end
    %% update flow
    u = u + u_next;
    v = v + v_next;
    
end

plot_flow(img2, u, v);
h = gcf;
saveas(h, sprintf('%s_flow.png', name));
