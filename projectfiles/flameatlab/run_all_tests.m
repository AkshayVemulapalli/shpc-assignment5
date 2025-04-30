% Unified driver for all test functions
% Adds libflameatlab to the MATLAB path
pathstoadd = genpath('../../libflameatlab');
addpath(pathstoadd);

% Set matrix dimensions
m = 6;
n = 4;

fprintf('\n==== Running FLAME Test Suite ====\n');

% ----- Test 1: syrk_ln_blk_var1 -----
A = randi([1,3], [m, n]);
C_temp = randi([-3, 3], [m, m]);
C1 = tril(C_temp) + tril(C_temp, -1)';
C1 = tril(C1);
expected1 = tril(A * (A.') + C1);

result1 = syrk_ln_blk_var1(A, C1);
if isequal(result1, expected1)
    fprintf('All is well for : syrk_ln_blk_var1\n');
else
    fprintf('Trouble in paradise : syrk_ln_blk_var1\n');
end

% ----- Test 2: syrk_ln_unb_var1 -----
A = randi([1,3], [m, n]);
C_temp = randi([-3, 3], [m, m]);
C2 = tril(C_temp) + tril(C_temp, -1)';
C2 = tril(C2);
expected2 = tril(A * (A.') + C2);

result2 = syrk_ln_unb_var1(A, C2);
if isequal(result2, expected2)
    fprintf('All is well for : syrk_ln_unb_var1\n');
else
    fprintf('Trouble in paradise : syrk_ln_unb_var1\n');
end

% ----- Test 3: trmm_lunn_blk_var1 -----
B = randi([1,3], [m, n]);
U_temp = randi([-3, 3], [m, m]);
U = triu(U_temp);

expected3 = U * B;
result3 = trmm_lunn_blk_var1(U, B);
if isequal(result3, expected3)
    fprintf('All is well for : trmm_lunn_blk_var1\n');
else
    fprintf('Trouble in paradise : trmm_lunn_blk_var1\n');
end

% ----- Test 4: trmm_lunn_unb_var1 -----
B = randi([1,3], [m, n]);
U_temp = randi([-3, 3], [m, m]);
U = triu(U_temp);

expected4 = (U * B);
result4 = trmm_lunn_unb_var1(U, B);
if isequal(result4, expected4)
    fprintf('All is well for: trmm_lunn_unb_var1\n');
else
    fprintf('Trouble in paradise: trmm_lunn_unb_var1\n');
end

fprintf('==== Tests Complete ====\n');
