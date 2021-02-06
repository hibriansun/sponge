#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

using namespace std;

ByteStream::ByteStream(const size_t capacity) : capacity(capacity){}

size_t ByteStream::write(const string &data) {
    size_t len = data.length();
    if(len > capacity - buffer_size()){
        len = capacity - buffer_size();
    }

    totalWrite += len;          // for bytes_written function

    for(size_t i = 0; i < len; i++){
        Deque.push_back(data[i]);
    }

    return len;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    size_t length = len;

    if(length > buffer_size()){
        length = buffer_size();
    }

    return string().assign(Deque.begin(), Deque.begin()+length);
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    size_t length = len;

    if(length > buffer_size()){
        length = buffer_size();
    }

    totalRead += length;
    
    while(length--){
        Deque.pop_front();
    }

    return;
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    string rtn = peek_output(len);
    pop_output(len);

    return rtn;
}

void ByteStream::end_input() {endOfStream = true;}

bool ByteStream::input_ended() const { return endOfStream; }

size_t ByteStream::buffer_size() const { return Deque.size(); }

bool ByteStream::buffer_empty() const { return buffer_size() == 0; }

bool ByteStream::eof() const { return buffer_empty() && input_ended(); }

size_t ByteStream::bytes_written() const { return totalWrite; }

size_t ByteStream::bytes_read() const { return totalRead; }

size_t ByteStream::remaining_capacity() const {
     return capacity - buffer_size(); 
}
