#once
#bankdef b4
{
    #addr 0x00
    #addr_end 0xff
    #outp 8 * 0x00
	#bits 8
	; this is used to make sure that
	; each label is aligned to the sector grid
	#labelalign 128
}

registerA = 0x0
registerB = 0x8
noValue = 0x0

#subruledef register
{
    a => registerA
    b => registerB
}

#subruledef flag
{
    i => 0x0
    z => 0x1
    e => 0x2
    s => 0x3
	
    o => 0x4
    nz => 0x5
    ne => 0x6
    ns => 0x7
}

#ruledef
{
	; Variable Mode

	ldi {value: u4},{r: register} =>
	{
		temp = (r | 0)
		value @ temp`4
	}
	
	ld [{value: u4}],{r: register} =>
	{
		temp = (r | 1)
		value @ temp`4
	}
	
	cmp {f: flag} =>
	{
        assert(flag >= i)
        assert(flag <= s)
		temp = (registerA | 4)
		flagCut = (0`4 | (flag & 0x3))
		flagCut @ temp`4
	}
	
	cmp {f: flag} =>
	{
        assert(flag >= o)
		temp = (registerB | 4)
		flagCut = (0`4 | (flag & 0x3))
		flagCut @ temp`4
	}
	
	st {r: register},[{value: u4}] =>
	{
		temp = (r | 5)
		value @ temp`4
	}
	
	jp {r: register},{value: u4} =>
	{
		temp = (r | 6)
		value @ temp`4
	}
	
	jpc {r: register},{value: u4} =>
	{
		temp = (r | 7)
		value @ temp`4
	}
	
	
	; Mode A
	add {value: u4} =>
	{
		temp = (registerA | 2)
		value @ temp`4
	}
	
	nand {value: u4},a =>
	{
		temp = (registerA | 3)
		value @ temp`4
	}
	
	jpn {value: u4} =>
	{
		temp = (registerA | 6)
		value @ temp`4
	}
	
	jpcn {value: u4} =>
	{
		temp = (registerA | 7)
		value @ temp`4
	}
	
	; Mode B	
	add b =>
	{
		temp = (registerB | 2)
		noValue @ temp`4
	}
	
	jpf {addr: u8} =>
	{
		temp = (registerB | 6)
		shortAddr = (addr & 0xF0) >> 4;
		shortAddr`4 @ temp`4
	}
	
	jpcf {addr: u8} =>
	{
		temp = (registerB | 7)
		shortAddr = (addr & 0xF0) >> 4;
		shortAddr`4 @ temp`4
	}
}