c
c     $Id: testf.cpp,v 1.1.1.1 1994-03-29 06:44:33 d3g681 Exp $
c

c
c     Exercise the MA routines.
c

      program testf

      implicit none

      integer handle1
      integer handle2
      integer handle3
      integer handle4
      integer i
      integer ihandle1
      integer index1
      integer index2
      logical value

#include "mafdecls.h"

c     ok
      write (*,*) 'start testing MA_set_error_print ...'
      value = MA_set_error_print(.true.)
      write (*,*) 'should see an MA error message here ...'
      value = MA_pop_stack(-1)
      value = MA_set_error_print(.false.)
      if (value) then
          write (*,*) 'should not see an MA error message here ...'
          value = MA_pop_stack(-1)
      else
          write (*,*) '... failure; return value is wrong'
      endif
      write (*,*) 'stop testing MA_set_error_print'
      write (*,*) ' '

      value = MA_set_error_print(.true.)

c     ok
      write (*,*) 'should be 9 values ...'
      write (*,*) '1. MA_sizeof(MT_BYTE, 1, MT_BYTE) = ',
     $    MA_sizeof(MT_BYTE, 1, MT_BYTE)
      write (*,*) '2. MA_sizeof(MT_INT, 1, MT_BYTE) = ',
     $    MA_sizeof(MT_INT, 1, MT_BYTE)
      write (*,*) '3. MA_sizeof(MT_LOG, 1, MT_BYTE) = ',
     $    MA_sizeof(MT_LOG, 1, MT_BYTE)
      write (*,*) '4. MA_sizeof(MT_REAL, 1, MT_BYTE) = ',
     $    MA_sizeof(MT_REAL, 1, MT_BYTE)
      write (*,*) '5. MA_sizeof(MT_DBL, 1, MT_BYTE) = ',
     $    MA_sizeof(MT_DBL, 1, MT_BYTE)
      write (*,*) '6. MA_sizeof(MT_SCPL, 1, MT_BYTE) = ',
     $    MA_sizeof(MT_SCPL, 1, MT_BYTE)
      write (*,*) '7. MA_sizeof(MT_DCPL, 1, MT_BYTE) = ',
     $    MA_sizeof(MT_DCPL, 1, MT_BYTE)
      write (*,*) '8. MA_sizeof(MT_BYTE, 3, MT_DBL) = ',
     $    MA_sizeof(MT_BYTE, 3, MT_DBL)
      write (*,*) '9. MA_sizeof(MT_BYTE, 33, MT_DBL) = ',
     $    MA_sizeof(MT_BYTE, 33, MT_DBL)
      write (*,*) ' '

c     ok
      write (*,*) 'should be 2 values ...'
      write (*,*) '1. MA_sizeof_overhead(MT_BYTE) = ',
     $    MA_sizeof_overhead(MT_BYTE)
      write (*,*) '2. MA_sizeof_overhead(MT_INT) = ',
     $    MA_sizeof_overhead(MT_INT)
      write (*,*) ' '

c     fail
      write (*,*) 'should fail (not init) ...'
      value = MA_push_stack(MT_DBL, 10, 'stack1', handle1)
      if (value) then
          write (*,*) '... success'
      else
          write (*,*) '... failure'
      endif
      write (*,*) ' '

c     fail
      write (*,*) 'should fail (bad datatype) ...'
      value = MA_init(-1, 10, 10)
      if (value) then
          write (*,*) '... success'
      else
          write (*,*) '... failure'
      endif
      write (*,*) ' '

c     ok
      write (*,*) 'should succeed ...'
      value = MA_init(MT_DBL, 1000, 1000)
      if (value) then
          write (*,*) '... success'
      else
          write (*,*) '... failure'
      endif
      write (*,*) ' '

c     ok
      write (*,*) 'should be 1 value ...'
      write (*,*) '1. MA_sizeof_overhead(MT_BYTE) = ',
     $    MA_sizeof_overhead(MT_BYTE)
      write (*,*) ' '

c     fail
      write (*,*) 'should fail (bad handle) ...'
      handle1 = 0
      value = MA_pop_stack(handle1)
      if (value) then
          write (*,*) '... success'
      else
          write (*,*) '... failure'
      endif
      write (*,*) ' '

c     fail
      write (*,*) 'should fail (bad handle) ...'
      handle1 = 37
      value = MA_pop_stack(handle1)
      if (value) then
          write (*,*) '... success'
      else
          write (*,*) '... failure'
      endif
      write (*,*) ' '

c     fail
      write (*,*) 'should fail (bad handle) ...'
      handle1 = 10000
      value = MA_pop_stack(handle1)
      if (value) then
          write (*,*) '... success'
      else
          write (*,*) '... failure'
      endif
      write (*,*) ' '

c     fail
      write (*,*) 'should fail (bad handle) ...'
      value = MA_get_index(handle1, index1)
      if (value) then
          write (*,*) '... success'
      else
          write (*,*) '... failure'
      endif
      write (*,*) ' '

c     ok
      write (*,*) 'start testing MA_chop_stack ...'
      value = MA_push_stack(MT_BYTE, 1, 'stack1', handle1)
      value = MA_push_stack(MT_BYTE, 2, 'stack2', handle2)
      value = MA_push_stack(MT_BYTE, 3, 'stack3', handle3)
      value = MA_push_stack(MT_BYTE, 4, 'stack4', handle4)
      write (*,*) 'should be 4 blocks on stack ...'
      call MA_summarize_allocated_blocks
      write (*,*) 'should succeed ...'
      value = MA_chop_stack(handle4)
      if (value) then
          write (*,*) '... success'
      else
          write (*,*) '... failure'
      endif
      write (*,*) 'should be 3 blocks on stack ...'
      call MA_summarize_allocated_blocks
      write (*,*) 'should fail (not in stack) ...'
      value = MA_chop_stack(handle4)
      if (value) then
          write (*,*) '... success'
      else
          write (*,*) '... failure'
      endif
      write (*,*) 'should succeed ...'
      value = MA_chop_stack(handle2)
      if (value) then
          write (*,*) '... success'
      else
          write (*,*) '... failure'
      endif
      write (*,*) 'should be 1 block on stack ...'
      call MA_summarize_allocated_blocks
      write (*,*) 'should succeed ...'
      value = MA_chop_stack(handle1)
      if (value) then
          write (*,*) '... success'
      else
          write (*,*) '... failure'
      endif
      write (*,*) 'should be 0 blocks ...'
      call MA_summarize_allocated_blocks
      value = MA_push_stack(MT_BYTE, 1, 'stack1', handle1)
      do 10 i = 1, 33
          value = MA_push_stack(MT_BYTE, 1, 'stackn', handle2)
10    continue
      value = MA_chop_stack(handle1)
      write (*,*) 'stop testing MA_chop_stack'
      write (*,*) ' '

c     ok
      write (*,*) 'should succeed ...'
      value = MA_push_stack(MT_DBL, 10, 'stack1', handle1)
      if (value) then
          write (*,*) '... success'
      else
          write (*,*) '... failure'
      endif
      write (*,*) 'should succeed ...'
      value = MA_get_index(handle1, index1)
      if (value) then
          write (*,*) '... success'
      else
          write (*,*) '... failure'
      endif
      dbl_mb(index1) = 19.82
      dbl_mb(index1 + 9) = dbl_mb(index1) - 19
      write (*,*) 'should be 19.82 and 0.82 ...'
      write (*,*) 'dbl_mb(', index1, ') = ', dbl_mb(index1)
      write (*,*) 'dbl_mb(', index1 + 9, ') = ', dbl_mb(index1 + 9)
      write (*,*) ' '

c     ok
      write (*,*) 'should succeed ...'
      value = MA_allocate_heap(MT_INT, 10, 'heap1', handle2)
      if (value) then
          write (*,*) '... success'
      else
          write (*,*) '... failure'
      endif
      write (*,*) ' '

c     fail
      write (*,*) 'should fail (not in heap) ...'
      value = MA_free_heap(handle1)
      if (value) then
          write (*,*) '... success'
      else
          write (*,*) '... failure'
      endif
      write (*,*) ' '

c     fail
      write (*,*) 'should fail (not in stack) ...'
      value = MA_pop_stack(handle2)
      if (value) then
          write (*,*) '... success'
      else
          write (*,*) '... failure'
      endif
      write (*,*) ' '

c     ok
      write (*,*) 'should succeed ...'
      value = MA_push_stack(MT_BYTE, 5, 'stack2', handle3)
      if (value) then
          write (*,*) '... success'
      else
          write (*,*) '... failure'
      endif
      write (*,*) ' '

c     ok
      write (*,*) 'should see something here ...'
      call MA_summarize_allocated_blocks
      write (*,*) ' '

c     fail
      write (*,*) 'should fail (not top of stack) ...'
      value = MA_pop_stack(handle1)
      if (value) then
          write (*,*) '... success'
      else
          write (*,*) '... failure'
      endif
      write (*,*) ' '

c     ok
      write (*,*) 'should succeed ...'
      value = MA_pop_stack(handle3)
      if (value) then
          write (*,*) '... success'
      else
          write (*,*) '... failure'
      endif
      write (*,*) ' '

c     ok
      write (*,*) 'should succeed ...'
      value = MA_pop_stack(handle1)
      if (value) then
          write (*,*) '... success'
      else
          write (*,*) '... failure'
      endif
      write (*,*) ' '

c     ok
      write (*,*) 'should succeed ...'
      value = MA_get_index(handle2, index2)
      if (value) then
          write (*,*) '... success'
      else
          write (*,*) '... failure'
      endif
      int_mb(index2) = 1963
      int_mb(index2 + 9) = int_mb(index2) - 1900
      write (*,*) 'should be 1963 and 63 ...'
      write (*,*) 'int_mb(', index2, ') = ', int_mb(index2)
      write (*,*) 'int_mb(', index2 + 9, ') = ', int_mb(index2 + 9)
      write (*,*) ' '

c     ok
      write (*,*) 'should succeed ...'
      value = MA_allocate_heap(MT_REAL, 1, 'heap2', handle3)
      if (value) then
          write (*,*) '... success'
      else
          write (*,*) '... failure'
      endif
      write (*,*) ' '

c     ok
      write (*,*) 'start testing MA_verify_allocator_stuff ...'
      write (*,*) 'should see nothing here ...'
      value = MA_verify_allocator_stuff()
      write (*,*) 'should succeed ...'
      if (value) then
          write (*,*) '... success'
      else
          write (*,*) '... failure'
      endif
      write (*,*) 'stop testing MA_verify_allocator_stuff'
      write (*,*) ' '

c     fail
      write (*,*) 'should fail (bad right guard) ...'
      int_mb(index2 + 10) = 0
      value = MA_free_heap(handle2)
      if (value) then
          write (*,*) '... success'
      else
          write (*,*) '... failure'
      endif
      write (*,*) ' '

c     ok
      write (*,*) 'should succeed ...'
      value = MA_set_auto_verify(.true.)
      value = MA_set_auto_verify(.true.)
      if (value) then
          write (*,*) '... success'
      else
          write (*,*) '... failure'
      endif
      write (*,*) ' '

c     fail
      write (*,*) 'start testing MA_set_auto_verify ...'
      write (*,*) 'should see something here ...'
      value = MA_set_auto_verify(.true.)
      value = MA_free_heap(handle2)
      write (*,*) 'should fail (bad right guard) ...'
      if (value) then
          write (*,*) '... success'
      else
          write (*,*) '... failure'
      endif
      value = MA_set_auto_verify(.false.)
      write (*,*) 'stop testing MA_set_auto_verify'
      write (*,*) ' '

c     fail
      write (*,*) 'start testing MA_verify_allocator_stuff ...'
      write (*,*) 'should see something here ...'
      value = MA_verify_allocator_stuff()
      write (*,*) 'should fail (bad right guard) ...'
      if (value) then
          write (*,*) '... success'
      else
          write (*,*) '... failure'
      endif
      write (*,*) 'stop testing MA_verify_allocator_stuff'
      write (*,*) ' '

c     ok
      write (*,*) 'should be 3 values ...'
      write (*,*) '1. MA_inquire_avail(MT_DBL) = ',
     $    MA_inquire_avail(MT_DBL)
      write (*,*) '2. MA_inquire_avail(MT_BYTE) = ',
     $    MA_inquire_avail(MT_BYTE)
      write (*,*) '3. MA_inquire_avail(MT_DCPL) = ',
     $    MA_inquire_avail(MT_DCPL)
      write (*,*) ' '

c     fail
      write (*,*) 'should be 3 values ...'
      write (*,*) '1. MA_inquire_heap(MT_DBL) = ',
     $    MA_inquire_heap(MT_DBL)
      write (*,*) '2. MA_inquire_heap(MT_BYTE) = ',
     $    MA_inquire_heap(MT_BYTE)
      write (*,*) '3. MA_inquire_heap(MT_DCPL) = ',
     $    MA_inquire_heap(MT_DCPL)
      write (*,*) ' '

c     fail
      write (*,*) 'should be 3 values ...'
      write (*,*) '1. MA_inquire_stack(MT_DBL) = ',
     $    MA_inquire_stack(MT_DBL)
      write (*,*) '2. MA_inquire_stack(MT_BYTE) = ',
     $    MA_inquire_stack(MT_BYTE)
      write (*,*) '3. MA_inquire_stack(MT_DCPL) = ',
     $    MA_inquire_stack(MT_DCPL)
      write (*,*) ' '

c     ok
      write (*,*) 'should succeed ...'
      value = MA_alloc_get(MT_INT, 1, 'heap3', handle1, index1)
      if (value) then
          write (*,*) '... success'
      else
          write (*,*) '... failure'
      endif
      int_mb(index1) = 1982
      write (*,*) 'should be 1982 ...'
      write (*,*) 'int_mb(', index1, ') = ', int_mb(index1)
      write (*,*) ' '

c     ok
      write (*,*) 'should succeed ...'
      value = MA_free_heap(handle1)
      if (value) then
          write (*,*) '... success'
      else
          write (*,*) '... failure'
      endif
      write (*,*) ' '

c     ok
      write (*,*) 'should succeed ...'
      value = MA_push_get(MT_INT, 1, 'stack3', handle1, index1)
      if (value) then
          write (*,*) '... success'
      else
          write (*,*) '... failure'
      endif
      int_mb(index1) = 5
      write (*,*) 'should be 5 ...'
      write (*,*) 'int_mb(', index1, ') = ', int_mb(index1)
      write (*,*) ' '

c     ok
      write (*,*) 'should succeed ...'
      value = MA_pop_stack(handle1)
      if (value) then
          write (*,*) '... success'
      else
          write (*,*) '... failure'
      endif
      write (*,*) ' '

c     ok
      write (*,*) 'start testing MA_print_stats ...'
      call MA_print_stats
      write (*,*) 'stop testing MA_print_stats'
      write (*,*) ' '

c     fail
      write (*,*) 'should fail (not implemented) ...'
      value = MA_init_memhandle_iterator(ihandle1)
      if (value) then
          write (*,*) '... success'
      else
          write (*,*) '... failure'
      endif
      write (*,*) ' '

c     fail
      write (*,*) 'should fail (not implemented) ...'
      value = MA_get_next_memhandle(ihandle1, handle1)
      if (value) then
          write (*,*) '... success'
      else
          write (*,*) '... failure'
      endif
      write (*,*) ' '

c     ok
      write (*,*) 'start testing MA_set_hard_fail ...'
      value = MA_set_hard_fail(.false.)
      write (*,*) 'should see a (nonfatal) MA error message here ...'
      value = MA_pop_stack(-1)
      value = MA_set_hard_fail(.true.)
      value = MA_set_hard_fail(.true.)
      if (value) then
          write (*,*) 'should see a (hard failure)',
     $    ' MA error message here ...'
          value = MA_pop_stack(-1)
      else
          write (*,*) '... failure; return value is wrong'
      endif
      write (*,*) 'stop testing MA_set_hard_fail'

      end
