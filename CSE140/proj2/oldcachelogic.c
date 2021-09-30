#include "tips.h"
#include <stdbool.h>

/* The following two functions are defined in util.c */

/* finds the highest 1 bit, and returns its position, else 0xFFFFFFFF */
unsigned int uint_log2(word w); 

/* return random int from 0..x-1 */
int randomint( int x );

/*
  This function allows the lfu information to be displayed

    assoc_index - the cache unit that contains the block to be modified
    block_index - the index of the block to be modified

  returns a string representation of the lfu information
 */
char* lfu_to_string(int assoc_index, int block_index)
{
  /* Buffer to print lfu information -- increase size as needed. */
  static char buffer[9];
  sprintf(buffer, "%u", cache[assoc_index].block[block_index].accessCount);

  return buffer;
}

/*
  This function allows the lru information to be displayed

    assoc_index - the cache unit that contains the block to be modified
    block_index - the index of the block to be modified

  returns a string representation of the lru information
 */
char* lru_to_string(int assoc_index, int block_index)
{
  /* Buffer to print lru information -- increase size as needed. */
  static char buffer[9];
  sprintf(buffer, "%u", cache[assoc_index].block[block_index].lru.value);

  return buffer;
}

/*
  This function initializes the lfu information

    assoc_index - the cache unit that contains the block to be modified
    block_number - the index of the block to be modified

*/
void init_lfu(int assoc_index, int block_index)
{
  cache[assoc_index].block[block_index].accessCount = 0;
}

/*
  This function initializes the lru information

    assoc_index - the cache unit that contains the block to be modified
    block_number - the index of the block to be modified

*/
void init_lru(int assoc_index, int block_index)
{
  cache[assoc_index].block[block_index].lru.value = 0;
}

/*
  This is the primary function you are filling out,
  You are free to add helper functions if you need them

  @param addr 32-bit byte address
  @param data a pointer to a SINGLE word (32-bits of data)
  @param we   if we == READ, then data used to return
              information back to CPU

              if we == WRITE, then data used to
              update Cache/DRAM
*/
void accessMemory(address addr, word* data, WriteEnable we)
{
  /* Declare variables here */
    //Used for finding the tag, index and offset
    unsigned int indexLength; unsigned int offsetLength; unsigned int tagLength;
    unsigned int indexValue; unsigned int offsetValue; unsigned int tagValue;
    unsigned int temp;
    char buffer[400]; //For printing
    TransferUnit tu;

    //Other useful variables
    //int numBlocks;
    bool hit = false; //Tell us whether we've had a cache hit or not
    int lruBlock = -1;
    int toBeReplaced = -1;
    address memAddr;

    

  /* handle the case of no cache at all - leave this in */
  if(assoc == 0) {
    accessDRAM(addr, (byte*)data, WORD_SIZE, we);
    return;
  }

  /*
  You need to read/write between memory (via the accessDRAM() function) and
  the cache (via the cache[] global structure defined in tips.h)

  Remember to read tips.h for all the global variables that tell you the
  cache parameters

  The same code should handle random, LFU, and LRU policies. Test the policy
  variable (see tips.h) to decide which policy to execute. The LRU policy
  should be written such that no two blocks (when their valid bit is VALID)
  will ever be a candidate for replacement. In the case of a tie in the
  least number of accesses for LFU, you use the LRU information to determine
  which block to replace.

  Your cache should be able to support write-through mode (any writes to
  the cache get immediately copied to main memory also) and write-back mode
  (and writes to the cache only gets copied to main memory when the block
  is kicked out of the cache.

  Also, cache should do allocate-on-write. This means, a write operation
  will bring in an entire block if the block is not already in the cache.

  To properly work with the GUI, the code needs to tell the GUI code
  when to redraw and when to flash things. Descriptions of the animation
  functions can be found in tips.h
  */

  /* Start adding code here */


    //The address of the cache we need is stored in addr
    //First we should calculate the length of the index, offset, and tag
    indexLength = uint_log2(set_count);
    offsetLength = uint_log2(block_size);
    tagLength = 32 - indexLength - offsetLength;

    //Now that we have that we need to figure out what their values are by using shifts
    //The layout of the cache address should be tag at the left, then index, then offset

    //Find offset, which should be the rightmost offsetLength bits  
    temp = addr << (32 - offsetLength);
    offsetValue = temp >> (32 - offsetLength);

    //Find the index, which is tagLength bits from the left and offsetLength bits from the right
    temp = addr << tagLength;
    indexValue = temp >> (32 - indexLength);
    sprintf(buffer, "Index Value: %d\n", indexValue);
    append_log(buffer);

    //Find the tag, which is the leftmost tagLength bits
    tagValue = addr >> (offsetLength + indexLength);
    /*sprintf(buffer, "Tag Value: %d\n", tagValue);
    append_log(buffer);*/

    //Find the TransferUnit
    switch(block_size) {
        case 1: tu = BYTE_SIZE; break;
        case 2: tu = HALF_WORD_SIZE; break;
        case 4: tu = WORD_SIZE; break;
        case 8: tu = DOUBLEWORD_SIZE; break;
        case 16: tu = QUADWORD_SIZE; break;
        case 32: tu = OCTWORD_SIZE; break;
    }
    
   
    
    //Now that everything is decoded we can look at the cache
    //This is the case where cache is just being read, and the memory is not being updated
    if(we == READ) {
        //Iterate through each block in the row corresponding to the index
        for(int i = 0; i < assoc; i++) {
            //If the block is valid and the tag matches, we have a hit
            if(cache[indexValue].block[i].valid == VALID && cache[indexValue].block[i].tag == tagValue) {
                hit = true;
                //cache[indexValue].block[i].accessCount++;
                //Highlight the right word green
                highlight_offset(indexValue, i, offsetValue, HIT);
                if(policy == LRU) {
                    //Make this the first most recently used block
                    cache[indexValue].block[i].lru.value = 1;
                    lruBlock = i;
                }

                //Find the right offset within the block and return it
                memcpy(data, cache[indexValue].block[i].data + offsetValue, WORD_SIZE);
                break;

            }
        }
        //If hit is still false, we have a cache miss
        if(hit == false) {
            //Check if there's an empty block
            for(int i = assoc; i >= 0; i--) {
                if(cache[indexValue].block[i].valid == INVALID) {
                    toBeReplaced = i; //We want to replace an empty block before we replace a full one
                }
            }
            //If there are no empty blocks then choose based on the replacement policy
            if(toBeReplaced != -1) {
                if(policy == LRU) {
                    //Find the LRU block
                    for(int i = 0; i < assoc; i++) {
                        if(cache[indexValue].block[i].lru.value == assoc) { //Find the block in last place
                            lruBlock = i;
                            toBeReplaced = i;
                        }
                    }
                }
                //Otherwise the replacement policy is random
                else {
                    toBeReplaced = rand() % (assoc + 1);
                }
            }
            //If the block is dirty then the memory needs to be updated before it's discarded
            if(cache[indexValue].block[toBeReplaced].dirty == DIRTY && memory_sync_policy == WRITE_BACK) {
                //The memory adress is the tag value on the left and then then the index value
                memAddr = (cache[indexValue].block[toBeReplaced].tag << indexLength) | indexValue;
                accessDRAM(memAddr, (cache[indexValue].block[toBeReplaced].data), tu, we);
                cache[indexValue].block[toBeReplaced].dirty = VIRGIN;
            }
            highlight_offset(indexValue, toBeReplaced, offsetValue, MISS);
            highlight_block(indexValue, toBeReplaced);
            //Load the cache block from memory
            accessDRAM(addr, cache[indexValue].block[toBeReplaced].data, tu, we);
            //Update all the information for this block
            cache[indexValue].block[toBeReplaced].valid = VALID;
            cache[indexValue].block[toBeReplaced].dirty = VIRGIN;
            cache[indexValue].block[toBeReplaced].tag = tagValue;
            if(policy == LRU) {
                 cache[indexValue].block[toBeReplaced].lru.value = 1; //This block is new so it's in first place
            }
        }
        //Update the LRUs
        if(policy == LRU) {
           for(int i = 0; i < assoc; i++) {
                if(cache[indexValue].block[i].lru.value != 0 && i != lruBlock) 
                    cache[indexValue].block[i].lru.value++;
           }
        }
    }
    
    //This is the case where the memory is being updated
    /*if(we == WRITE) {
        //Iterate through each block in the row corresponding to the index
        for(int i = 0; i < assoc; i++) {
            //If the block is valid and the tag matches, we have a hit
            if(cache[indexValue].block[i].valid == VALID && cache[indexValue].block[i].tag == tagValue) {
                hit = true;
                //Find the right offset within the block and update the cache value

                if(policy == LRU) {
                    //Check the LRU bit, and if the current block is the LRU block set the LRU block to be this one
                }
            }
        }
        //If hit is still false, we have a cache miss
        if(!hit) {
            //If the block is dirty then the memory needs to be updated before it's discarded
            if(cache[indexVaue].block[i].dirty == DIRTY && memory_sync_policy == WRITE_BACK) {
                //Update the memory

            }
            if(policy == LRU) {
                //Check if the LRU block is set to anything
                if( ) {
                    //Discard the LRU block
    
                    //Load the cache block from memory, and set this block as the LRU
                }
            } 
            //Otherwise the replacement policy is random
            else {
                //Pick a random number between 0 and assoc, and discard that block

                //Load the cache block from memory, and set this block as the LRU
            }
        }
    }*/



accessDRAM(addr, (byte*)data, WORD_SIZE, we);







}
