/*
main reference: https://www.codeproject.com/Articles/1264257/Socket-Programming-in-Cplusplus-using-boost-asio-T
todo:
-use asynchronous server
-design a class for handler the connections with real error handler
*/
#include <iostream>
#include <algorithm>  
//#include <netinet/in.h>
//#include <sys/socket.h>
//#include <unistd.h>
#include <string>
//I use asio because is multiplatform, so, we can move this code to other systems easily
// additionally, asi have asynchronous server, so it can be good for manage many massages from diferent clients. (not used)
#include <boost/asio.hpp> 

using namespace boost::asio;
using ip::tcp;
// use only the name we need from std namespace instead of import them all
using std::string;
using std::cout;
using std::endl;


#define PORT 8080 //receiving port

class reverseEcho{
    public:
        string greeting = "Hello from c++ server";
        string lengthError = "Message must be less that 50 characteres";   
        void receive(tcp::socket & socket);
        void send(tcp::socket & socket);
        void reverseVal(void);
        reverseEcho(); //constructor   
    private:
        string valReceived;
        string valReversed;
};

reverseEcho::reverseEcho(void) {
    cout << greeting << endl;  //just dummy constructor, something moro todo
}

void reverseEcho::receive(tcp::socket & socket) {  //use tcp socket for comunication
    boost::asio::streambuf buffer1; //object for manage the stream of input data
    boost::asio::read_until(socket, buffer1, "\n"); //keep reading until receiving a end of line
    valReceived = boost::asio::buffer_cast<const char*>(buffer1.data());
}

void reverseEcho::send(tcp::socket & socket){  
    if (valReversed.size() > 50){
        const string msg = lengthError + "\n"; 
        boost::asio::write( socket, boost::asio::buffer(msg));
    } else {
        const string msg = valReversed + "\n"; //put the end of line for let the client know when message ends
        boost::asio::write( socket, boost::asio::buffer(msg));
    }
}

void reverseEcho::reverseVal(void) { 
    // Use of reverse from algorithm header
    string str = valReceived;
    reverse(str.begin(), str.end());
    valReversed = str;
    //this is a simple function but is implemented as a function in case of future upgrades like print values
}

int main()
{
    try 
    {
    //I create the socket and listener out of the class in case we need to use many ports or endpoints or read one socket and send with other
    //basic asio object:
        boost::asio::io_service io_service;
    //set endpoint and listen for new connection
        tcp::endpoint ep = tcp::endpoint(tcp::v4(), PORT );
        tcp::acceptor acceptor_(io_service, ep); //fancy way of set ip and port
    //socket creation for use un reverseEcho class
        tcp::socket socket_(io_service);
        cout << "listening at endpoint " << ep << endl;
    //create a reverseEcho object
        reverseEcho re;

    //waiting for connection
        acceptor_.accept(socket_);
        cout << "Client connected" << endl;
    //wait for compleate a received message
        re.receive(socket_);
        cout << "Message received" << endl;

    //reverse the message
        re.reverseVal();
        cout << "Message reversed" << endl;
        
    //send reversed message
        re.send(socket_);
        cout << "Message sended" << endl;
    }
    catch(std::exception& e)
    {
    std::cerr << e.what() << endl;
    }
    return 0;
}
