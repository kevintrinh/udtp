
#ifndef __UDTP_THREAD_PROCESS
#define __UDTP_THREAD_PROCESS
#include <fstream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "UDTPChunk.h"
#include <queue>
#include "UDTPThread.h"

class UDTPThreadProcess : public UDTPThread{ /*This thread, which is not bound by any socket or peer, handles the identification of UDTPChunks!*/
    public:
        void queue_chunk(UDTPChunk newChunk){
            _queueChunks.push(newChunk);
        } /*Adds a chunk to its queue.*/
        void add_failed_chunk_id(unsigned int peerID, unsigned int queueFailedChunkID){
            _queueFailedPeerID.push(peerID);
            _queueFailedChunkID.push(queueFailedChunkID);
        }

        ~UDTPThreadProcess(){
            _peer = NULL;
        }

        UDTPChunk next_chunk(){
            return _queueChunks.front();
        }
        bool pop_chunk(){
            _queueChunks.pop();
            return true;
        }


        bool pop_failed_chunk(){
            _queueFailedPeerID.pop();
            _queueFailedChunkID.pop();
        }
    bool set_peer(UDTPPeer* peer){
        _peer = peer;
    }
    UDTPPeer* peer(){
        return _peer;
    }
    private:
        UDTPPeer* _peer;
        std::queue<UDTPChunk> _queueChunks;
        std::queue<unsigned int> _queueFailedPeerID; /*Parallel!*/
        std::queue<unsigned int> _queueFailedChunkID;
};

#endif
