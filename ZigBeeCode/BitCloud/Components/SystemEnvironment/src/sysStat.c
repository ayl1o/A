/**************************************************************************//**
\file  sysStat.c

\brief Collection of internal runtime data for report

\author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

\internal
  History:
    15/04/11 D. Loskutnikov - Created
  Last modified:
    $Id: sysStat.c 27654 2015-02-25 08:41:27Z mukesh.basrani $
*******************************************************************************/
#if defined(_STATS_ENABLED_)

/******************************************************************************
                   Includes section
******************************************************************************/
#include <sysQueue.h>
#include <sysStat.h>
#include <statStack.h>

/******************************************************************************
                   Extern variables section
******************************************************************************/
#ifdef __GNUC__
#ifdef BOARD_SAMR21
//extern unsigned int __stack_bottom;
//extern unsigned int __stack_top;
extern unsigned short __stack_start;
extern unsigned short __stack;
#else
extern unsigned short __stack_start;
extern unsigned short __stack;
#endif
#endif

/******************************************************************************
                    Static functions prototypes section
******************************************************************************/
static uint8_t measureStack(uint8_t *buf, uint8_t maxSize);

/******************************************************************************
                    Static variables section
******************************************************************************/
// Create queue with one preincluded generator 

static SYS_StatGenerator_t stackStatGenerator = {.gen = measureStack, .next = NULL};
static QueueDescriptor_t statGenerators = {.head = (QueueElement_t*) &stackStatGenerator};


/******************************************************************************
                    Implementation section
******************************************************************************/

/**************************************************************************//**
\brief Register new generator of stat data

\param[in] gen - generator
******************************************************************************/
void SYS_RegisterStatGenerator(SYS_StatGenerator_t *gen)
{
  putQueueElem(&statGenerators, gen);
}

/**************************************************************************//**
\brief Collect stats from registered generators into the supplied buffer

\param[out] buf - buffer to place stat report
\param[in] maxSize - size limit of buffer
\return number of actually placed bytes
******************************************************************************/
uint8_t SYS_GenerateStatReport(uint8_t *buf, uint8_t maxSize)
{
  const SYS_StatGenerator_t *gen;
  uint8_t *p = buf;

  // Assume generators are polite and won't make maxSize negative
  for (gen = getQueueElem(&statGenerators); gen && maxSize; gen = getNextQueueElem(gen))
  {
    uint8_t size = gen->gen(p, maxSize);
    maxSize -= size;
    p += size;
  }
  return p - buf;
}

/**************************************************************************//**
\brief Stat generator for reporting stacks usage

\param[out] buf - output buffer
\param[in] maxSize - buffer size limit
\return number of bytes actually written
******************************************************************************/
#if (defined(__ICCAVR__) || defined(__ICCARM__))
static uint8_t measureStack(uint8_t *buf, uint8_t maxSize)
{
  #pragma section = "CSTACK"
  #pragma section = "RSTACK"
  uint16_t used;

  if (maxSize < 2)
    return 0;

  used = probeStack(__segment_begin("CSTACK"), __segment_end("CSTACK"));
  memcpy(buf, &used, 2);

  if (maxSize < 4)
    return 2;

  used = probeStack(__segment_begin("RSTACK"), __segment_end("RSTACK"));
  memcpy(buf + 2, &used, 2);

  return 4;
}
#elif defined(__GNUC__)
static uint8_t measureStack(uint8_t *buf, uint8_t maxSize)
{
#ifdef BOARD_PC
  (void ) buf;
  (void) maxSize;
  return 0;
#else
  uint16_t used;

  if (maxSize < 2)
    return 0;
  used = probeStack((((volatile uint8_t *)&__stack_start)+STACK_INIT_MARGIN), ((volatile uint8_t *)&__stack));

  memcpy(buf, &used, 2);

  return 2;
#endif
}

#endif

/**************************************************************************//**
\brief Measures stack and returns

\param[out] None
\param[in] None
\return number of actually placed bytes
******************************************************************************/
uint16_t SYS_StatGetMinimumStackLeft(void)
{
#ifdef BOARD_PC
  return SYS_STACK_CHECK_DISABLED;

#else
  char  buf[4] = {'A','A'};
  volatile uint16_t cstackMaxSize = 0;
  
  uint8_t returnedBytes = SYS_GenerateStatReport((uint8_t*)buf, 2);
  if(returnedBytes >= 2)
  {
#if (defined(__ICCAVR__) || defined(__ICCARM__))  
    #pragma section = "CSTACK"
    uint16_t cstack = ( (uint16_t)buf[0] | (((uint16_t)buf[1]) << 8u) );
    //\note rstack could also be retrieved by increasing the buffer size to 4
    volatile uint8_t* pCStackEnd = __segment_end("CSTACK");
    volatile uint8_t* pCStackBegin = __segment_begin("CSTACK");

#elif defined(__GNUC__)

    volatile uint8_t* pCStackEnd = (uint8_t *)&__stack;
    volatile uint8_t* pCStackBegin = (uint8_t *)&__stack_start;
    uint16_t cstack = ( (uint16_t)buf[0] | (((uint16_t)buf[1]) << 8u) );  
#endif
    cstackMaxSize = (uint16_t) (pCStackEnd - pCStackBegin);
    return (cstackMaxSize - cstack);
  }

  return SYS_STACK_CHECK_DISABLED;
#endif  
}


#endif // _STATS_ENABLED_
// eof sysStat.c
