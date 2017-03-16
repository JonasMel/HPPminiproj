int get_file_size(const char* fileName);

int read_file_into_buffer(const char* fileName, unsigned char* buf, int bufSz);

int write_buffer_to_file(const char* fileName, const unsigned char* buf, int bufSz);
