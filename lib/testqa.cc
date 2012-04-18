#include "qa_utils.h"
#include <volk/volk.h>
#include <boost/test/unit_test.hpp>

//VOLK_RUN_TESTS(volk_16i_x5_add_quad_16i_x4_a, 1e-4, 2046, 10000);
//VOLK_RUN_TESTS(volk_16i_branch_4_state_8_a, 1e-4, 2046, 10000);
VOLK_RUN_TESTS(volk_16ic_s32f_deinterleave_real_32f_a, 1e-5, 32768.0, 20460, 1);
VOLK_RUN_TESTS(volk_16ic_deinterleave_real_8i_a, 0, 0, 20460, 1);
VOLK_RUN_TESTS(volk_16ic_deinterleave_16i_x2_a, 0, 0, 20460, 1);
VOLK_RUN_TESTS(volk_16ic_s32f_deinterleave_32f_x2_a, 1e-4, 32768.0, 20460, 1);
VOLK_RUN_TESTS(volk_16ic_deinterleave_real_16i_a, 0, 0, 20460, 1);
VOLK_RUN_TESTS(volk_16ic_magnitude_16i_a, 1, 0, 20460, 1);
VOLK_RUN_TESTS(volk_16ic_s32f_magnitude_32f_a, 1e-5, 32768.0, 20460, 1);
VOLK_RUN_TESTS(volk_16i_s32f_convert_32f_a, 1e-4, 32768.0, 20460, 1);
VOLK_RUN_TESTS(volk_16i_s32f_convert_32f_u, 1e-4, 32768.0, 20460, 1);
VOLK_RUN_TESTS(volk_16i_convert_8i_a, 0, 0, 20460, 1);
VOLK_RUN_TESTS(volk_16i_convert_8i_u, 0, 0, 20460, 1);
//VOLK_RUN_TESTS(volk_16i_max_star_16i_a, 0, 0, 20460, 10000);
//VOLK_RUN_TESTS(volk_16i_max_star_horizontal_16i_a, 0, 0, 20460, 10000);
//VOLK_RUN_TESTS(volk_16i_permute_and_scalar_add_a, 1e-4, 0, 2046, 1000);
//VOLK_RUN_TESTS(volk_16i_x4_quad_max_star_16i_a, 1e-4, 0, 2046, 1000);
VOLK_RUN_TESTS(volk_16u_byteswap_a, 0, 0, 20460, 1);
VOLK_RUN_TESTS(volk_32f_accumulator_s32f_a, 1e-4, 0, 20460, 1);
VOLK_RUN_TESTS(volk_32f_x2_add_32f_a, 1e-4, 0, 20460, 1);
VOLK_RUN_TESTS(volk_32f_x2_add_32f_u, 1e-4, 0, 20460, 1);
VOLK_RUN_TESTS(volk_32fc_32f_multiply_32fc_a, 1e-4, 0, 20460, 1);
VOLK_RUN_TESTS(volk_32fc_s32f_power_32fc_a, 1e-4, 0, 20460, 1);
VOLK_RUN_TESTS(volk_32f_s32f_calc_spectral_noise_floor_32f_a, 1e-4, 20.0, 20460, 1);
VOLK_RUN_TESTS(volk_32fc_s32f_atan2_32f_a, 1e-4, 10.0, 20460, 1);
//VOLK_RUN_TESTS(volk_32fc_x2_conjugate_dot_prod_32fc_a, 1e-4, 0, 2046, 10000);
VOLK_RUN_TESTS(volk_32fc_x2_conjugate_dot_prod_32fc_u, 1e-4, 0, 20460, 1);
VOLK_RUN_TESTS(volk_32fc_deinterleave_32f_x2_a, 1e-4, 0, 20460, 1);
VOLK_RUN_TESTS(volk_32fc_deinterleave_64f_x2_a, 1e-4, 0, 20460, 1);
VOLK_RUN_TESTS(volk_32fc_s32f_deinterleave_real_16i_a, 0, 32768, 20460, 1);
VOLK_RUN_TESTS(volk_32fc_deinterleave_real_32f_a, 1e-4, 0, 20460, 1);
VOLK_RUN_TESTS(volk_32fc_deinterleave_real_64f_a, 1e-4, 0, 20460, 1);
VOLK_RUN_TESTS(volk_32fc_x2_dot_prod_32fc_a, 1e-4, 0, 204600, 1);
VOLK_RUN_TESTS(volk_32fc_index_max_16u_a, 3, 0, 20460, 1);
VOLK_RUN_TESTS(volk_32fc_s32f_magnitude_16i_a, 1, 32768, 20460, 1);
VOLK_RUN_TESTS(volk_32fc_magnitude_32f_a, 1e-4, 0, 20460, 1);
VOLK_RUN_TESTS(volk_32f_s32f_convert_16i_a, 1, 32768, 20460, 1);
VOLK_RUN_TESTS(volk_32f_s32f_convert_16i_u, 1, 32768, 20460, 1);
VOLK_RUN_TESTS(volk_32f_s32f_convert_32i_a, 1, 2<<31, 20460, 1);
VOLK_RUN_TESTS(volk_32f_s32f_convert_32i_u, 1, 2<<31, 20460, 1);
VOLK_RUN_TESTS(volk_32f_convert_64f_a, 1e-4, 0, 20460, 1);
VOLK_RUN_TESTS(volk_32f_convert_64f_u, 1e-4, 0, 20460, 1);
VOLK_RUN_TESTS(volk_32f_s32f_convert_8i_a, 1, 128, 20460, 1);
VOLK_RUN_TESTS(volk_32f_s32f_convert_8i_u, 1, 128, 20460, 1);
//VOLK_RUN_TESTS(volk_32fc_s32f_x2_power_spectral_density_32f_a, 1e-4, 2046, 10000);
VOLK_RUN_TESTS(volk_32fc_s32f_power_spectrum_32f_a, 1e-4, 0, 2046, 1);
VOLK_RUN_TESTS(volk_32fc_x2_square_dist_32f_a, 1e-4, 0, 20460, 1);
VOLK_RUN_TESTS(volk_32fc_x2_s32f_square_dist_scalar_mult_32f_a, 1e-4, 10, 20460, 1);
VOLK_RUN_TESTS(volk_32f_x2_divide_32f_a, 1e-4, 0, 20460, 1);
VOLK_RUN_TESTS(volk_32f_x2_dot_prod_32f_a, 1e-4, 0, 204600, 1);
VOLK_RUN_TESTS(volk_32f_x2_dot_prod_32f_u, 1e-4, 0, 204600, 1);
//VOLK_RUN_TESTS(volk_32f_s32f_32f_fm_detect_32f_a, 1e-4, 2046, 10000);
VOLK_RUN_TESTS(volk_32f_index_max_16u_a, 3, 0, 20460, 1);
VOLK_RUN_TESTS(volk_32f_x2_s32f_interleave_16ic_a, 1, 32767, 20460, 1);
VOLK_RUN_TESTS(volk_32f_x2_interleave_32fc_a, 0, 0, 20460, 1);
VOLK_RUN_TESTS(volk_32f_x2_max_32f_a, 1e-4, 0, 20460, 1);
VOLK_RUN_TESTS(volk_32f_x2_min_32f_a, 1e-4, 0, 20460, 1);
VOLK_RUN_TESTS(volk_32f_s32f_normalize_a, 1e-4, 100, 20460, 1);
VOLK_RUN_TESTS(volk_32f_s32f_power_32f_a, 1e-4, 4, 20460, 1);
VOLK_RUN_TESTS(volk_32f_sqrt_32f_a, 1e-4, 0, 20460, 1);
VOLK_RUN_TESTS(volk_32f_s32f_stddev_32f_a, 1e-4, 100, 20460, 1);
VOLK_RUN_TESTS(volk_32f_stddev_and_mean_32f_x2_a, 1e-4, 0, 20460, 1);
VOLK_RUN_TESTS(volk_32f_x2_subtract_32f_a, 1e-4, 0, 20460, 1);
VOLK_RUN_TESTS(volk_32f_x3_sum_of_poly_32f_a, 1e-4, 0, 20460, 1);
VOLK_RUN_TESTS(volk_32i_x2_and_32i_a, 0, 0, 20460, 1);
VOLK_RUN_TESTS(volk_32i_s32f_convert_32f_a, 1e-4, 100, 20460, 1);
VOLK_RUN_TESTS(volk_32i_s32f_convert_32f_u, 1e-4, 100, 20460, 1);
VOLK_RUN_TESTS(volk_32i_x2_or_32i_a, 0, 0, 20460, 1);
VOLK_RUN_TESTS(volk_32u_byteswap_a, 0, 0, 20460, 1);
//VOLK_RUN_TESTS(volk_32u_popcnt_a, 0, 0, 2046, 10000);
VOLK_RUN_TESTS(volk_64f_convert_32f_a, 1e-4, 0, 20460, 1);
VOLK_RUN_TESTS(volk_64f_convert_32f_u, 1e-4, 0, 20460, 1);
VOLK_RUN_TESTS(volk_64f_x2_max_64f_a, 1e-4, 0, 20460, 1);
VOLK_RUN_TESTS(volk_64f_x2_min_64f_a, 1e-4, 0, 20460, 1);
VOLK_RUN_TESTS(volk_64u_byteswap_a, 0, 0, 20460, 1);
//VOLK_RUN_TESTS(volk_64u_popcnt_a, 0, 0, 2046, 10000);
VOLK_RUN_TESTS(volk_8ic_deinterleave_16i_x2_a, 0, 0, 20460, 1);
VOLK_RUN_TESTS(volk_8ic_s32f_deinterleave_32f_x2_a, 1e-4, 100, 20460, 1);
VOLK_RUN_TESTS(volk_8ic_deinterleave_real_16i_a, 0, 256, 20460, 1);
VOLK_RUN_TESTS(volk_8ic_s32f_deinterleave_real_32f_a, 1e-4, 100, 20460, 1);
VOLK_RUN_TESTS(volk_8ic_deinterleave_real_8i_a, 0, 0, 20460, 1);
VOLK_RUN_TESTS(volk_8ic_x2_multiply_conjugate_16ic_a, 0, 0, 20460, 1);
VOLK_RUN_TESTS(volk_8ic_x2_s32f_multiply_conjugate_32fc_a, 1e-4, 100, 20460, 1);
VOLK_RUN_TESTS(volk_8i_convert_16i_a, 0, 0, 20460, 1);
VOLK_RUN_TESTS(volk_8i_convert_16i_u, 0, 0, 20460, 1);
VOLK_RUN_TESTS(volk_8i_s32f_convert_32f_a, 1e-4, 100, 20460, 1);
VOLK_RUN_TESTS(volk_8i_s32f_convert_32f_u, 1e-4, 100, 20460, 1);
VOLK_RUN_TESTS(volk_32fc_x2_multiply_32fc_a, 1e-4, 0, 20460, 1);
VOLK_RUN_TESTS(volk_32fc_x2_multiply_32fc_u, 1e-4, 0, 20460, 1);
VOLK_RUN_TESTS(volk_32fc_x2_multiply_conjugate_32fc_a, 1e-4, 0, 20460, 1);
VOLK_RUN_TESTS(volk_32fc_x2_multiply_conjugate_32fc_u, 1e-4, 0, 20460, 1);
VOLK_RUN_TESTS(volk_32fc_conjugate_32fc_a, 1e-4, 0, 20460, 1);
VOLK_RUN_TESTS(volk_32fc_conjugate_32fc_u, 1e-4, 0, 20460, 1);
VOLK_RUN_TESTS(volk_32f_x2_multiply_32f_a, 1e-4, 0, 20460, 1);
VOLK_RUN_TESTS(volk_32f_x2_multiply_32f_u, 1e-4, 0, 20460, 1);
VOLK_RUN_TESTS(volk_32fc_s32fc_multiply_32fc_a, 1e-4, 0, 20460, 1);
VOLK_RUN_TESTS(volk_32fc_s32fc_multiply_32fc_u, 1e-4, 0, 20460, 1);
VOLK_RUN_TESTS(volk_32f_s32f_multiply_32f_a, 1e-4, 0, 20460, 1);
VOLK_RUN_TESTS(volk_32f_s32f_multiply_32f_u, 1e-4, 0, 20460, 1);
