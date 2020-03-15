#pragma once
#include "Internal/IConnection.h"
#include "Internal/IIPendpoint.h"

#pragma warning(push)
#pragma warning(disable:26812 6385 6255 6387 6258 6001 26495 26444 26451 28251)
#include "boost/asio/io_context.hpp"
#include "boost/asio/ip/tcp.hpp"
#include "boost/asio/ip/udp.hpp"
#pragma warning(pop)

#include <variant>

namespace DynabyteSoftware
{
  namespace Networking
  {
    namespace BoostImplementation
    {
      class Connection : public virtual Internal::IConnection
      {
      public:
        #pragma region Constructors
        //Connection(const Internal::IIPendpoint& endpoint, TransportProtocol protocol = TransportProtocol::TCP);
        //Connection(const std::shared_ptr<boost::asio::io_context>& context);
        #pragma endregion

      private:
        #pragma region Variables
        std::shared_ptr<boost::asio::io_context> _context;
        std::variant < std::unique_ptr<boost::asio::ip::tcp::socket>,
                       std::unique_ptr<boost::asio::ip::udp::socket> > _socket;
        #pragma endregion

        #pragma region Constructors
        #pragma endregion
      };
    }
  }
}