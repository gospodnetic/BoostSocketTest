
#include <iostream>
#include <boost/asio.hpp>

#include <boost/array.hpp>

using boost::asio::ip::tcp;

class Caller
{
  public:
    initialize()
    {
        *m_resolver = resolver(m_io_service);
    }

    boost::asio::io_service     m_io_service;
    tcp::resolver*              m_resolver;
    tcp::resolver::query*       m_query;
    tcp::resolver::iterator     m_end;

    tcp::socket*                m_socket;
    boost::system::error_code   m_error;

}

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 3)
        {
            std::cerr << "Usage: client <host>" << std::endl;
            return 1;
        }
        boost::asio::io_service io_service;
        tcp::resolver resolver(io_service);
        tcp::resolver::query query(argv[1], argv[2], boost::asio::ip::resolver_query_base::numeric_service);
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        tcp::resolver::iterator end;

        tcp::socket socket(io_service);
        boost::system::error_code error = boost::asio::error::host_not_found;
        while(error && endpoint_iterator != end)
        {
            socket.close();
            socket.connect(*endpoint_iterator++, error);
        }
        for(;;)
        {
            boost::array<char, 128> buffer;
            boost::system::error_code error;

            size_t len = socket.read_some(boost::asio::buffer(buffer), error);

            if (error == boost::asio::error::eof)
                break;
            else if (error)
                throw boost::system::system_error(error);

            std::cout.write(buffer.data(), len);
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }


    return 0;
}
