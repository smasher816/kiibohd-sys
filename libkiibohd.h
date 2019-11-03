// Modules
#include "Macro/PartialMap/kll.h"
#include "Macro/PartialMap/kll.h"
#include "Macro/PixelMap/pixel.h"

// main.c
int Host_init();
int Host_register_callback( void* func );
int Host_cli_process();
int Host_periodic();
int Host_poll();
int Host_process();
int Host_set_systick( uint32_t systick_ms );
int Host_set_nanosecs_since_systick( uint32_t systick_ns );
int Host_callback_test();

// Macro/PartialMap/result.c
typedef struct ResultCapabilityStackItem {
	TriggerMacro *trigger;
	uint8_t       state;
	uint8_t       stateType;
	uint8_t       capabilityIndex;
	uint8_t      *args;
} ResultCapabilityStackItem;

typedef struct ResultCapabilityStack {
	ResultCapabilityStackItem stack[ ResultCapabilityStackSize_define ];
	uint8_t                   size;
} ResultCapabilityStack;
