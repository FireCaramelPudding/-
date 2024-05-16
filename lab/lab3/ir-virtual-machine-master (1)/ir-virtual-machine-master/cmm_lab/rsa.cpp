#include "rsa.h"

int rsa_keygen(struct RSA rsa_keygen_rsa[1], int rsa_keygen_bits, int rsa_keygen_e)
{
	int rsa_keygen_primes = 2;
	int rsa_keygen_r0,
		rsa_keygen_r1,
		rsa_keygen_r2,
		rsa_keygen_tmp,
		rsa_keygen_prime,
		rsa_keygen_prime_out[1],
		rsa_keygen_prev_prime,
		rsa_keygen_inv[1];
	int rsa_keygen_n = 0, rsa_keygen_bitsr[2];
	int rsa_keygen_i = 0,
		rsa_keygen_j,
		rsa_keygen_quo = 0,
		rsa_keygen_rmd = 0;
	int rsa_keygen_continue_outer = 1;
	int rsa_keygen_goto_redo = 1;
	int rsa_keygen_loop_inner = 1;

	if (mod(rsa_keygen_e, 2) == 0 || rsa_keygen_e <= 1)
	{
		return 0;
	}

	rsa_keygen_quo = rsa_keygen_bits / rsa_keygen_primes;
	rsa_keygen_rmd = mod(rsa_keygen_bits, rsa_keygen_primes);

	rsa_keygen_i = 0;
	while (rsa_keygen_i < rsa_keygen_primes)
	{
		if (rsa_keygen_i < rsa_keygen_rmd)
		{
			rsa_keygen_bitsr[rsa_keygen_i] = rsa_keygen_quo + 1;
		}
		else
		{
			rsa_keygen_bitsr[rsa_keygen_i] = rsa_keygen_quo;
		}

		rsa_keygen_i = rsa_keygen_i + 1;
	}

	rsa_keygen_rsa[0].e = rsa_keygen_e;

	rsa_keygen_i = 0;
	while (rsa_keygen_i < rsa_keygen_primes)
	{
		rsa_keygen_continue_outer = 0;

		rsa_keygen_loop_inner = 1;
		while (rsa_keygen_loop_inner)
		{
			// redo:
			rsa_keygen_goto_redo = 1;
			while (rsa_keygen_loop_inner && rsa_keygen_goto_redo)
			{
				rsa_keygen_goto_redo = 0;

				if (!generate_prime(rsa_keygen_prime_out, rsa_keygen_bitsr[rsa_keygen_i], 0, -1, -1))
				{
					return 0;
				}

				rsa_keygen_prime = rsa_keygen_prime_out[0];

				rsa_keygen_j = 0;
				while (!rsa_keygen_goto_redo && rsa_keygen_j < rsa_keygen_i)
				{
					if (rsa_keygen_j == 0)
					{
						rsa_keygen_prev_prime = rsa_keygen_rsa[0].p;
					}
					else
					{
						rsa_keygen_prev_prime = rsa_keygen_rsa[0].q;
					}

					if (rsa_keygen_prime == rsa_keygen_prev_prime)
					{
						rsa_keygen_goto_redo = 1;
					}

					if (!rsa_keygen_goto_redo)
					{
						rsa_keygen_j = rsa_keygen_j + 1;
					}
				}

				if (!rsa_keygen_goto_redo)
				{
					rsa_keygen_r2 = rsa_keygen_prime - 1;
					if (inverse_mod(rsa_keygen_inv, rsa_keygen_r2, rsa_keygen_rsa[0].e))
					{
						rsa_keygen_loop_inner = 0;
					}
				}
			}
		}

		if (rsa_keygen_i == 0)
		{
			rsa_keygen_rsa[0].p = rsa_keygen_prime;
		}
		else
		{
			rsa_keygen_rsa[0].q = rsa_keygen_prime;
		}

		if (rsa_keygen_i == 1)
		{
			rsa_keygen_r1 = rsa_keygen_rsa[0].p * rsa_keygen_rsa[0].q;
		}
		else
		{
			rsa_keygen_continue_outer = 1;
		}

		if (!rsa_keygen_continue_outer)
		{
			rsa_keygen_rsa[0].n = rsa_keygen_r1;
		}

		rsa_keygen_i = rsa_keygen_i + 1;
	}

	if (rsa_keygen_rsa[0].p < rsa_keygen_rsa[0].q)
	{
		rsa_keygen_tmp = rsa_keygen_rsa[0].p;
		rsa_keygen_rsa[0].p = rsa_keygen_rsa[0].q;
		rsa_keygen_rsa[0].q = rsa_keygen_tmp;
	}

	rsa_keygen_r1 = rsa_keygen_rsa[0].p - 1;
	rsa_keygen_r2 = rsa_keygen_rsa[0].q - 1;
	rsa_keygen_r0 = rsa_keygen_r1 * rsa_keygen_r2;

	if (!inverse_mod(rsa_keygen_inv, rsa_keygen_rsa[0].e, rsa_keygen_r0))
	{
		return 0;
	}

	rsa_keygen_rsa[0].d = rsa_keygen_inv[0];

	return 1;
}

int rsa_pubkey_encryrpt(
	int rsa_pubkenc_c_out[1],
	struct RSA rsa_pubkenc_rsa[1],
	int rsa_pubkenc_p)
{
	int rsa_pubkenc_c;

	if (rsa_pubkenc_rsa[0].n <= rsa_pubkenc_rsa[0].e ||
		cmp_uint32(rsa_pubkenc_p, rsa_pubkenc_rsa[0].n) >= 0)
	{
		return 0;
	}

	rsa_pubkenc_c = exp_mod(
		rsa_pubkenc_p, rsa_pubkenc_rsa[0].e, rsa_pubkenc_rsa[0].n);
	rsa_pubkenc_c_out[0] = rsa_pubkenc_c;

	return 1;
}

int rsa_privkey_encryrpt(
	int rsa_privkenc_c_out[1],
	struct RSA rsa_privkenc_rsa[1],
	int rsa_privkenc_p)
{
	int rsa_privkenc_c;

	if (cmp_uint32(rsa_privkenc_p, rsa_privkenc_rsa[0].n) >= 0)
	{
		return 0;
	}

	rsa_privkenc_c = exp_mod(
		rsa_privkenc_p, rsa_privkenc_rsa[0].d, rsa_privkenc_rsa[0].n);
	rsa_privkenc_c_out[0] = rsa_privkenc_c;

	return 1;
}

int rsa_privkey_decryrpt(
	int rsa_privkdec_p_out[1],
	struct RSA rsa_privkdec_rsa[1],
	int rsa_privkdec_c)
{
	int rsa_privkdec_p;

	if (cmp_uint32(rsa_privkdec_c, rsa_privkdec_rsa[0].n) >= 0)
	{
		return 0;
	}

	rsa_privkdec_p = exp_mod(
		rsa_privkdec_c, rsa_privkdec_rsa[0].d, rsa_privkdec_rsa[0].n);
	rsa_privkdec_p_out[0] = rsa_privkdec_p;

	return 1;
}

int rsa_pubkey_decryrpt(
	int rsa_pubkdec_p_out[1],
	struct RSA rsa_pubkdec_rsa[1],
	int rsa_pubkdec_c)
{
	int rsa_pubkdec_p;

	if (rsa_pubkdec_rsa[0].n <= rsa_pubkdec_rsa[0].e ||
		cmp_uint32(rsa_pubkdec_c, rsa_pubkdec_rsa[0].n) >= 0)
	{
		return 0;
	}

	rsa_pubkdec_p = exp_mod(
		rsa_pubkdec_c, rsa_pubkdec_rsa[0].e, rsa_pubkdec_rsa[0].n);
	rsa_pubkdec_p_out[0] = rsa_pubkdec_p;

	return 1;
}