#pragma once
#include "Internal/IServer.h"

#pragma warning(push)
#pragma warning(disable:26812 6385 6255 6387 6258 6001 26495 26444 26451 28251)
#include "boost/asio/io_context.hpp"
#include "boost/asio/ip/tcp.hpp"
#pragma warning(pop)

#include <variant>

namespace DynabyteSoftware
{
  namespace Networking
  {
    namespace BoostImplementation
    {
      class Server : public virtual Internal::IServer
      {
      public:
        #pragma region Constructors
        Server(uint16_t port);
        #pragma endregion

        #pragma region IServer
        virtual std::future<Networking::Connection> accept() override;
        #pragma endregion
      private:
        #pragma region Variables
        std::shared_ptr<boost::asio::io_context> _context;
        boost::asio::ip::tcp::acceptor _acceptor;
        #pragma endregion
      };
    }
  }
}