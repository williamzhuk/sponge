#include "byte_stream.hh"

#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <vector>

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

using namespace std;

ByteStream::ByteStream(const size_t cap): capacity(cap) {}

size_t ByteStream::write(const string &data) {
    if (!isOpen) return 0;
    size_t i = 0;
    for (; i<data.size() && buffer.size()<capacity; i++) {
        buffer.push_back(data[i]);
        num_written++;
    }
    return i;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    string ans;
    for(size_t i = 0; i<len && i<buffer.size(); i++) {
        ans += buffer[i];
    }
    return ans;
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    size_t max_pop_length = min(len, buffer.size());
    for(size_t i = 0; i<max_pop_length; i++) {
        buffer.pop_front();
        num_popped++;
    }
}

void ByteStream::end_input() {
    isOpen = false;
}

bool ByteStream::input_ended() const {
    return !isOpen;
}

size_t ByteStream::buffer_size() const {
    return buffer.size();
}

bool ByteStream::buffer_empty() const {
    return buffer.size()==0;
}

bool ByteStream::eof() const {
    return input_ended() && buffer_empty();
}

size_t ByteStream::bytes_written() const {
    return num_written;
}

size_t ByteStream::bytes_read() const {
    return num_popped;
}

size_t ByteStream::remaining_capacity() const {
    return capacity-buffer.size(); 
}
