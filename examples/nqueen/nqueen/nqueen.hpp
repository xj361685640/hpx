/*
 * nqueen.hpp
 *      Author: vamatya
 */


#include <hpx/runtime.hpp>
#include <hpx/runtime/components/client_base.hpp>

#include "stubs/nqueen.hpp"


namespace hpx { namespace components
{
    class Board
        : public client_base<Board, stubs::Board>
    {
        typedef client_base<Board, stubs::Board> base_type;

    public:
        Board()
        {}
        Board(naming::id_type gid)
            : base_type(gid)
        {}

        void initBoard(unsigned int size, int level){
            BOOST_ASSERT(gid_);
            return this->base_type::initBoard(gid_, size, level);
        }

        void printBoard()
        {
            BOOST_ASSERT(gid_);
            return this->base_type::printBoard(gid_);
        }

        list_t accessBoard(){
            BOOST_ASSERT(gid_);
            return this->base_type::accessBoard(gid_);
        }

        lcos::future_value<list_t> accessBoard_async(){
            return this->base_type::accessBoard_async(gid_);
        }

        unsigned int getSize(){
            BOOST_ASSERT(gid_);
            return this->base_type::getSize(gid_);
        }

        lcos::future_value<unsigned int> getSize_async() {
            return this->base_type::getSize_async(gid_);
        }

        int getLevel(){
            BOOST_ASSERT(gid_);
            return this->base_type::getLevel(gid_);
        }

        lcos::future_value<int> getLevel_async() {
            return this->base_type::getLevel_async(gid_);
        }

        void updateBoard(int level, int pos){
            BOOST_ASSERT(gid_);
            return this->base_type::updateBoard(gid_, level, pos);
        }

        bool checkBoard(list_t list, int level){
            BOOST_ASSERT(gid_);
            return this->base_type::checkBoard(gid_, list, level);
        }

        lcos::future_value<bool> checkBoard_async(list_t list, int level){
            return this->base_type::checkBoard_async(gid_, list, level);
        }

        void solveNqueen(list_t list, unsigned int size, int level){
            BOOST_ASSERT(gid_);
            return this->base_type::solveNqueen(gid_, list, size, level);
        }

        void clearBoard(){
            BOOST_ASSERT(gid_);
            return this->base_type::clearBoard(gid_);
        }
        void testBoard(list_t list, unsigned int size, int level){
            BOOST_ASSERT(gid_);
            return this->base_type::testBoard(gid_, list, size, level);
        }

    };

}}

