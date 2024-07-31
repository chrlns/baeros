.section .text
.globl cpu_data_memory_barrier

cpu_data_memory_barrier:
push {r7}

# The read register Should Be Zero before the call
mov r7, #0		

# Invalidate Entire Data Cache		
mcr p15, 0, r7, c7, c6, 0

# Clean Entire Data Cache	
mcr p15, 0, r7, c7, c10, 0	

# Clean and Invalidate Entire Data Cache
mcr p15, 0, r7, c7, c14, 0

# Data Synchronization Barrier
mcr p15, 0, r7, c7, c10, 4		

# Data Memory Barrier
mcr p15, 0, r7, c7, c10, 5
   
pop {r7}
bx lr
