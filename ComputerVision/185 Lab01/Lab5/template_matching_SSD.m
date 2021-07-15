function [output, match] = template_matching_SSD(I1, template, threshold)
    shift_u = size(template, 2);
    shift_v = size(template, 1);
    for u = 1: size(I1, 2) - shift_u
        for v = 1: size(I1, 1) - shift_v
            x1 = u; x2 = u + shift_u - 1;
            y1 = v; y2 = v + shift_v - 1;
            patch = I1(y1:y2, x1:x2);
            % SSD
            X = patch - template;
            value = sum(X(:).^2);
            output(v, u) = value;
        end
    end
    match = (output < threshold);
end