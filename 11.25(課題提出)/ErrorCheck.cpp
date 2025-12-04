bool IntErrorCheck(const int* pointer) {
	return
		pointer == nullptr || *pointer == -1 ?  true : false;
}

bool DoubleErrorCheck(const double* pointer) {
	return
	pointer == nullptr || *pointer == -1.0 ? true : false;
}

bool FloatErrorCheck(const float* pointer) {
	return
	pointer == nullptr || *pointer == -1.0 ? true : false;
}

bool CharErrorCheck(const char* pointer) {
	return
	pointer == nullptr ? true : false;
}