% Unified driver for all test functions
% Adds libflameatlab to the MATLAB path
pathstoadd = genpath('../../libflameatlab');
addpath(pathstoadd);

% Set matrix dimensions
m = 36;
n = 24;

fprintf('\n==== Running FLAME Test Suite ====\n');

% ----- Operation 1: syrk_ln -----
A = randi([1,3], [m, n]); % random m x n matrix
C = randi([-3, 3], [m, m]); % random m x m matrix
C = tril(C); % C is a symmetric matrix, and we only store and update its lower triangle
nb_alg = 10;

syrk_ln_expected_output = tril(A * (A.') + C); % we tril matlab's output to match our format of only the lower triangle being stored 

% ----- Test 1: syrk_ln_blk_var1 -----
test1_result = syrk_ln_blk_var1(A, C, nb_alg);
if isequal(test1_result, syrk_ln_expected_output)
    fprintf('All is well for : syrk_ln_blk_var1\n');
else
    fprintf('Trouble in paradise : syrk_ln_blk_var1\n');
end

% ----- Test 2: syrk_ln_unb_var1 -----
test2_result = syrk_ln_unb_var1(A, C);
if isequal(test2_result, syrk_ln_expected_output)
    fprintf('All is well for : syrk_ln_unb_var1\n');
else
    fprintf('Trouble in paradise : syrk_ln_unb_var1\n');
end

% ----- Operation 2: trmm_lunn -----
B = randi([1,3], [m, n]);
U = randi([-3, 3], [m, m]);
U = triu(U);

trmm_lunn_expected_output = U * B;

% ----- Test 3: trmm_lunn_blk_var1 -----
test3_result = trmm_lunn_blk_var1(U, B, nb_alg);
if isequal(test3_result, trmm_lunn_expected_output)
    fprintf('All is well for : trmm_lunn_blk_var1\n');
else
    fprintf('Trouble in paradise : trmm_lunn_blk_var1\n');
end

% ----- Test 4: trmm_lunn_unb_var1 -----
test4_result = trmm_lunn_unb_var1(U, B);
if isequal(test4_result, trmm_lunn_expected_output)
    fprintf('All is well for : trmm_lunn_unb_var1\n');
else
    fprintf('Trouble in paradise: trmm_lunn_unb_var1\n');
end

fprintf('==== Tests Complete ====\n');
