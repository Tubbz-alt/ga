/*
 * $Id: f2c.c,v 1.1.1.1 1994-03-29 06:44:33 d3g681 Exp $
 */

/*
 * C wrapper routines.  In general, f2c_foo_ is called by FORTRAN routine
 * MA_foo, performs any necessary argument munging, then calls C routine
 * MA_foo.
 */

#include "ma.h"
#include "scope.h"

/**
 ** function types
 **/

private void fstring2cstring();

/**
 ** private routines
 **/

/* ------------------------------------------------------------------------- */
/*
 * Strip trailing blanks from fstring and copy it to cstring,
 * truncating if necessary to fit in cstring, and ensuring that
 * cstring is NUL-terminated.
 */
/* ------------------------------------------------------------------------- */

private void fstring2cstring(fstring, flength, cstring, clength)
    char	*fstring;	/* FORTRAN string */
    Integer	flength;	/* length of fstring */
    char	*cstring;	/* C buffer */
    Integer	clength;	/* max length (including NUL) of cstring */
{
    /* remove trailing blanks from fstring */
    while (flength-- && fstring[flength] == ' ')
        ;

    /* the postdecrement above went one too far */
    flength++;

    /* truncate fstring to cstring size */
    if (flength >= clength)
        flength = clength - 1;

    /* ensure that cstring is NUL-terminated */
    cstring[flength] = '\0';

    /* copy fstring to cstring */
    while (flength--)
        cstring[flength] = fstring[flength];
}

/**
 ** public routines
 **/

/* ------------------------------------------------------------------------- */
/*
 * 
 */
/* ------------------------------------------------------------------------- */

public Boolean f2c_alloc_get_(datatype, nelem, name, memhandle, index, namesize)
    Integer	*datatype;
    Integer	*nelem;
    char	*name;
    Integer	*memhandle;
    Integer	*index;
    Integer	namesize;	/* implicitly passed by FORTRAN */
{
    Boolean	value;
    char	buf[MA_NAMESIZE];

    /* ensure that name is NUL-terminated */
    fstring2cstring(name, namesize, buf, (Integer)sizeof(buf));

    value = MA_alloc_get(*datatype, *nelem, buf, memhandle, index);

    /* FORTRAN array indexing is 1-based, so increment index */
    (*index)++;

    return value;
}

/* ------------------------------------------------------------------------- */
/*
 * 
 */
/* ------------------------------------------------------------------------- */

public Boolean f2c_allocate_heap_(datatype, nelem, name, memhandle, namesize)
    Integer	*datatype;
    Integer	*nelem;
    char	*name;
    Integer	*memhandle;
    Integer	namesize;	/* implicitly passed by FORTRAN */
{
    char	buf[MA_NAMESIZE];

    /* ensure that name is NUL-terminated */
    fstring2cstring(name, namesize, buf, (Integer)sizeof(buf));

    return MA_allocate_heap(*datatype, *nelem, buf, memhandle);
}

/* ------------------------------------------------------------------------- */
/*
 * 
 */
/* ------------------------------------------------------------------------- */

public Boolean f2c_chop_stack_(memhandle)
    Integer	*memhandle;
{
    return MA_chop_stack(*memhandle);
}

/* ------------------------------------------------------------------------- */
/*
 * 
 */
/* ------------------------------------------------------------------------- */

public Boolean f2c_free_heap_(memhandle)
    Integer	*memhandle;
{
    return MA_free_heap(*memhandle);
}

/* ------------------------------------------------------------------------- */
/*
 * 
 */
/* ------------------------------------------------------------------------- */

public Boolean f2c_get_index_(memhandle, index)
    Integer	*memhandle;
    Integer	*index;
{
    Boolean	value = MA_get_index(*memhandle, index);

    /* FORTRAN array indexing is 1-based, so increment index */
    (*index)++;

    return value;
}

/* ------------------------------------------------------------------------- */
/*
 * 
 */
/* ------------------------------------------------------------------------- */

public Boolean f2c_get_next_memhandle_(ithandle, memhandle)
    Integer	*ithandle;
    Integer	*memhandle;
{
    return MA_get_next_memhandle(ithandle, memhandle);
}

/* ------------------------------------------------------------------------- */
/*
 * 
 */
/* ------------------------------------------------------------------------- */

public Boolean f2c_inform_base_(datatype, address1, address2)
    Integer	*datatype;
    Pointer	address1;
    Pointer	address2;
{
    return ma_inform_base(*datatype, address1, address2);
}

/* ------------------------------------------------------------------------- */
/*
 * 
 */
/* ------------------------------------------------------------------------- */

public Boolean f2c_init_(datatype, nominal_stack, nominal_heap)
    Integer	*datatype;
    Integer	*nominal_stack;
    Integer	*nominal_heap;
{
    return MA_init(*datatype, *nominal_stack, *nominal_heap);
}

/* ------------------------------------------------------------------------- */
/*
 * 
 */
/* ------------------------------------------------------------------------- */

public Boolean f2c_init_memhandle_iterator_(ithandle)
    Integer	*ithandle;
{
    return MA_init_memhandle_iterator(ithandle);
}

/* ------------------------------------------------------------------------- */
/*
 * 
 */
/* ------------------------------------------------------------------------- */

public Integer f2c_inquire_avail_(datatype)
    Integer	*datatype;
{
    return MA_inquire_avail(*datatype);
}

/* ------------------------------------------------------------------------- */
/*
 * 
 */
/* ------------------------------------------------------------------------- */

public Integer f2c_inquire_heap_(datatype)
    Integer	*datatype;
{
    return MA_inquire_heap(*datatype);
}

/* ------------------------------------------------------------------------- */
/*
 * 
 */
/* ------------------------------------------------------------------------- */

public Integer f2c_inquire_stack_(datatype)
    Integer	*datatype;
{
    return MA_inquire_stack(*datatype);
}

/* ------------------------------------------------------------------------- */
/*
 * 
 */
/* ------------------------------------------------------------------------- */

public Boolean f2c_pop_stack_(memhandle)
    Integer	*memhandle;
{
    return MA_pop_stack(*memhandle);
}

/* ------------------------------------------------------------------------- */
/*
 * 
 */
/* ------------------------------------------------------------------------- */

public void f2c_print_stats_()
{
    MA_print_stats();
}

/* ------------------------------------------------------------------------- */
/*
 * 
 */
/* ------------------------------------------------------------------------- */

public Boolean f2c_push_get_(datatype, nelem, name, memhandle, index, namesize)
    Integer	*datatype;
    Integer	*nelem;
    char	*name;
    Integer	*memhandle;
    Integer	*index;
    Integer	namesize;	/* implicitly passed by FORTRAN */
{
    Boolean	value;
    char	buf[MA_NAMESIZE];

    /* ensure that name is NUL-terminated */
    fstring2cstring(name, namesize, buf, (Integer)sizeof(buf));

    value = MA_push_get(*datatype, *nelem, buf, memhandle, index);

    /* FORTRAN array indexing is 1-based, so increment index */
    (*index)++;

    return value;
}

/* ------------------------------------------------------------------------- */
/*
 * 
 */
/* ------------------------------------------------------------------------- */

public Boolean f2c_push_stack_(datatype, nelem, name, memhandle, namesize)
    Integer	*datatype;
    Integer	*nelem;
    char	*name;
    Integer	*memhandle;
    Integer	namesize;	/* implicitly passed by FORTRAN */
{
    char	buf[MA_NAMESIZE];

    /* ensure that name is NUL-terminated */
    fstring2cstring(name, namesize, buf, (Integer)sizeof(buf));

    return MA_push_stack(*datatype, *nelem, buf, memhandle);
}

/* ------------------------------------------------------------------------- */
/*
 * 
 */
/* ------------------------------------------------------------------------- */

public Boolean f2c_set_auto_verify_(value)
    Integer	*value;
{
    return MA_set_auto_verify((Boolean)*value);
}

/* ------------------------------------------------------------------------- */
/*
 * 
 */
/* ------------------------------------------------------------------------- */

public Boolean f2c_set_error_print_(value)
    Integer	*value;
{
    return MA_set_error_print((Boolean)*value);
}

/* ------------------------------------------------------------------------- */
/*
 * 
 */
/* ------------------------------------------------------------------------- */

public Boolean f2c_set_hard_fail_(value)
    Integer	*value;
{
    return MA_set_hard_fail((Boolean)*value);
}

/* ------------------------------------------------------------------------- */
/*
 * 
 */
/* ------------------------------------------------------------------------- */

public Integer f2c_sizeof_(datatype1, nelem1, datatype2)
    Integer	*datatype1;
    Integer	*nelem1;
    Integer	*datatype2;
{
    return MA_sizeof(*datatype1, *nelem1, *datatype2);
}

/* ------------------------------------------------------------------------- */
/*
 * 
 */
/* ------------------------------------------------------------------------- */

public Integer f2c_sizeof_overhead_(datatype)
    Integer	*datatype;
{
    return MA_sizeof_overhead(*datatype);
}

/* ------------------------------------------------------------------------- */
/*
 * 
 */
/* ------------------------------------------------------------------------- */

public void f2c_summarize_allocated_blocks_()
{
    /* FORTRAN indices are 1-based */
    ma_summarize_allocated_blocks(1);
}

/* ------------------------------------------------------------------------- */
/*
 * 
 */
/* ------------------------------------------------------------------------- */

public Boolean f2c_verify_allocator_stuff_()
{
    return MA_verify_allocator_stuff();
}
