function [output, match] = template_matching_normcorr(I1, template, threshold)
    shift_u = size(template, 2);
    shift_v = size(template, 1);
    for u = 1: size(I1, 2) - shift_u
        for v = 1: size(I1, 1) - shift_v
            x1 = u; x2 = u + shift_u - 1;
            y1 = v; y2 = v + shift_v - 1;
            patch = I1(y1:y2, x1:x2);
            % Normalized Cross-Correlation
            v1 = reshape(patch, 1, []); %convert to vectors
            v2 = reshape(template, 1, []);
            v1 = v1 - mean(v1); %subtract the mean
            v2 = v2 - mean(v2);
            top = sum(v1.*v2);
            bottom = (sum(v1.^2) .* sum(v2.^2)).^0.5;
            value = top./bottom;
            %value = sum(v1 .* v2) ./ ((sum(v1.^2) .* sum(v2.^2)).^0.5); %normalize and take dot product
            output(v, u) = value;
        end
    end
match = (output > threshold);