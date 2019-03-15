#ifndef __MSTP_CPP_H__
#define __MSTP_CPP_H__
#include "mstp.h"
#include "ringbuf.h"

class Mstp
{
protected:
	/* Number of MS/TP Packets Rx/Tx */
	uint16_t packets;

	/* packet queues */
	DLMSTP_PACKET	Receive_Packet;


	/*RT_TASK Receive_Task, Fsm_Task;*/
	/* local MS/TP port data - shared with RS-485 */
	struct mstp_port_struct_t port;

	/* buffers needed by mstp port struct */
	uint8_t TxBuffer[MAX_MPDU];
	uint8_t RxBuffer[MAX_MPDU];

	/* data structure for MS/TP PDU Queue */
	struct mstp_pdu_packet
	{
		bool		data_expecting_reply;
		uint8_t		destination_mac;
		uint16_t	length;
		uint8_t		buffer[MAX_MPDU];
	};

	/* count must be a power of 2 for ringbuf library */
#ifndef MSTP_PDU_PACKET_COUNT
#define MSTP_PDU_PACKET_COUNT 8
#endif
	struct mstp_pdu_packet	PDU_Buffer[MSTP_PDU_PACKET_COUNT];
	RING_BUFFER				PDU_Queue;

	/* The minimum time without a DataAvailable or ReceiveError event */
	/* that a node must wait for a station to begin replying to a */
	/* confirmed request: 255 milliseconds. (Implementations may use */
	/* larger values for this timeout, not to exceed 300 milliseconds.) */
	uint16_t Treply_timeout = 300;

	/* The minimum time without a DataAvailable or ReceiveError event that a */
	/* node must wait for a remote node to begin using a token or replying to */
	/* a Poll For Master frame: 20 milliseconds. (Implementations may use */
	/* larger values for this timeout, not to exceed 100 milliseconds.) */
	uint8_t Tusage_timeout = 100;

	/* Timer that indicates line silence - and functions */
	struct timeval start;


public:
	Mstp(void);
	~Mstp(void);
public:
	void Init(void);
	bool LineActive(void);
	void RecvFrameFSM(void);
	void MasterNodeFSM(void);
	void SlaveNodeFSM(void);

	uint16_t CreateFrame(
		uint8_t *	buffer,			/* where frame is loaded */
		uint16_t	buffer_len,		/* amount of space available */
		uint8_t		frame_type,		/* type of frame to send - see defines */
		uint8_t		destination,	/* destination address */
		uint8_t		source,			/* source address */
		uint8_t *	data,			/* any data to be sent - may be null */
		uint16_t	data_len		/* number of bytes of data (up to 501) */
	);

	uint16_t PutReceive(void);
	uint16_t GetSend(unsigned timeout);  
	uint16_t GetReply(unsigned timeout); 
};

#endif//__MSTP_CPP_H__
