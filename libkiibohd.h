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

// Scan/TestIn/scan_loop.c
int Scan_setTriggerCode( uint8_t index, uint8_t type, uint8_t state );
int Scan_addScanCode( uint8_t index, uint8_t type );
int Scan_removeScanCode( uint8_t index, uint8_t type );

// Macro/PartialMap/macro.c
extern ResultsPending macroResultMacroPendingList;
extern index_uint_t macroTriggerMacroPendingList[];
extern index_uint_t macroTriggerMacroPendingListSize;
extern uint8_t capDebugMode;
uint8_t voteDebugMode;
uint8_t triggerPendingDebugMode;

// Macro debug flag - If set, clears the USB Buffers after signalling processing completion
// 1 - Disable USB output, show debug
// 2 - Enabled USB output, show debug
// 3 - Disable USB output
uint8_t macroDebugMode;

// Macro/PatialMap/layer.c
extern uint8_t layerDebugMode;
index_uint_t macroLayerIndexStack[ LayerNum ];
index_uint_t macroLayerIndexStackSize;
extern LayerStateType LayerState[];
extern const Layer LayerIndex[];

void Layer_clearLayers();
void Layer_layerStateSet( TriggerMacro *trigger, uint8_t state, uint8_t stateType, uint16_t layer, uint8_t layerState );

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

extern const Capability CapabilitiesList[];
extern ResultCapabilityStackItem resultCapabilityCallbackData;

extern const ResultMacro ResultMacroList[];
extern ResultMacroRecord ResultMacroRecordList[];

extern var_uint_t macroTriggerEventBufferSize;
extern TriggerEvent macroTriggerEventBuffer[];

// Macro/PixelMap/pixel.c
AnimationStack Pixel_AnimationStack;
uint16_t Pixel_AnimationStack_HostSize = Pixel_AnimationStackSize;
uint8_t  Pixel_Buffers_HostLen = Pixel_BuffersLen_KLL;
uint8_t  Pixel_MaxChannelPerPixel_Host = Pixel_MaxChannelPerPixel;
uint16_t Pixel_Mapping_HostLen = 128; // TODO Define
uint8_t  Pixel_AnimationStackElement_HostSize = sizeof( AnimationStackElement );
void Pixel_dispBuffer();
uint8_t Pixel_addAnimation( AnimationStackElement *element, CapabilityState cstate );
