#include "socket.hh"
#include "util.hh"

#include <cstdlib>
#include <iostream>

using namespace std;

void get_URL(const string &host, const string &path) {
    // Your code here.

    // You will need to connect to the "http" service on
    // the computer whose name is in the "host" string,
    // then request the URL path given in the "path" string.
    TCPSocket client_socket;
    Address destination(host, "http");              // Address (const std::string &hostname, const std::string &service)    Construct by resolving a hostname and servicename(cat /etc/services). More...
    client_socket.connect(destination);

    string request = "GET " + path + " HTTP/1.1\r\n" + "Host: " + host +"\r\n" + "Connection: close\r\n\r\n";
    client_socket.write(request);
    // Then you'll need to print out everything the server sends back,
    // (not just one call to read() -- everything) until you reach
    // the "eof" (end of file).

    // u can also replace "Connection: close\r\n" of the request string with code, `client_socket.shutdown(SHUT_WR)`.
    while(!client_socket.eof()){
        cout << client_socket.read();
    }
    
    client_socket.close();

    /*
    close与shutdown的区别:

    ①：close函数函数会关闭套接字，如果由其他进程共享着这个套接字，那么它仍然是打开的，这个连接仍然可以用来读和写。

    ②：shutdown会切断进程共享的套接字的所有连接，不管引用计数是否为0，由第二个参数(below)选择断连的方式。
        
        1.SHUT_RD：值为0，关闭连接的读这一半，套接字中不再有数据接收，且套接字接收缓冲区中的现有数据全都被丢弃，该套接字描述符不能再被进程调用，对端发送的数据会被确认，然后丢弃。

        2.SHUT_WR：值为1，关闭连接的写这一半。这称为半关闭，当前在套接字发送缓冲区数据被发送，然后连接终止序列。不论套接字描述符引用技术是否等于0，写半部都会被关闭。

        3.SHUT_RDWR：值为2，连接的读和写都关闭。相当于先调用SHUT_RD，再调用SHUT_WR。
    */

    return;
}

int main(int argc, char *argv[]) {
    try {
        if (argc <= 0) {
            abort();  // For sticklers: don't try to access argv[0] if argc <= 0.
        }

        // The program takes two command-line arguments: the hostname and "path" part of the URL.
        // Print the usage message unless there are these two arguments (plus the program name
        // itself, so arg count = 3 in total).
        if (argc != 3) {
            cerr << "Usage: " << argv[0] << " HOST PATH\n";
            cerr << "\tExample: " << argv[0] << " stanford.edu /class/cs144\n";
            return EXIT_FAILURE;
        }

        // Get the command-line arguments.
        const string host = argv[1];
        const string path = argv[2];

        // Call the student-written function.
        get_URL(host, path);
    } catch (const exception &e) {
        cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
