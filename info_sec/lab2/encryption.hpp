#pragma once

#include <sstream>
#include <fstream>
#include <memory>
#include "../lab1/math_method.hpp"

string read_dec(string file_name);
long long *read_enc(string file_name, uint64_t *length);
void write_enc(string file_name, long long *enc, uint64_t length);
void write_dec(string file_name, long long *dec, uint64_t length);
void write_ds(string file_name, long long S[]);

void find (long long *c, long long *d, long long p);
long long Shamir_code(string file_name);
long long Shamir_decode (string code, string key, string output);
void El_Gamala_coding(string file_name);
void El_Gamala_decoding(string code, string key, string output);
long long Vernam_coding(string file_name);
long long Vernam_decoding(string code, string key, string output);
void RSA_coding(string file_name);
void RSA_decoding(string code, string key, string output);
