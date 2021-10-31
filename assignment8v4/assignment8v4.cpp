
// This template.cpp is for PC users
// by Matthew Passarelli BCC B00255084
//

//#include "stdafx.h"
#include <iostream>

using namespace std;


int main(int argc, char* argv[])
{


    // Part A moves parts of 0xFACEC0FFB00255084 and 0xEEFEEDBADDDEED0F into 
    // different registers using pointers

    // Manually calculated results: EAX:, EBX:, ECX:, EDX:

    //  your properly formatted assembly language data here
    unsigned __int64 P8Anum1 = 0xFACEC0FFB0025508;
    unsigned __int64 P8Anum2 = 0xEEFEEDBADDDEED0F;

    __asm {
        //  your syntactically correct assembly language code here
        //  column alignment markers below (to guide you)
        //      |       |               |
        sub     eax, eax; clear eax
        sub     ebx, ebx; clear ebx
        sub     ecx, ecx; clear ecx
        sub     edx, edx; clear edx
        mov     eax, dword ptr P8Anum2 + 1; eax points to BADDDEED into eax
        mov     ebx, dword ptr P8Anum2 + 3; ebx points tdo FEEDBADD into ebx
        mov     ecx, dword ptr P8Anum1 + 2; ecx points to C0FFB002 into ecx
        mov     edx, dword ptr P8Anum1 + 4; edx points to FACEC0FF into edx
        mov     ax, word ptr P8Anum1 + 4; ax pointsto C0FF in ax
        mov     bx, word ptr P8Anum1 + 6; bx points to FACE
        mov     ch, byte ptr P8Anum2 + 7; ch points to EE
        mov     dh, byte ptr P8Anum2 + 0; dh points to 0F

        nop; no op for Part A break point

    }



    // Part B adds (0xFACE C0FF B002 5508) to (0xEEFE EDBA DDDE ED0F) using immediate addressing
    //   and dword pointers

    // Manually calculated results:
    // My calculated carry = 
    // My calculated sum = 0x1E9CD AEBA 8DE1 4217

    //  your properly formatted assembly language data here
    unsigned __int64 P8Bsum;
    char P8Bcarry;
    //clearRegisters();
    __asm {
        //  your syntactically correct assembly language code here
        //  column alignment markers below (to guide you)
        //      |       |               |                  
        sub     eax, eax; clear eax
        sub     ebx, ebx; clear ebx
        sub     ecx, ecx; clear ecx
        sub     edx, edx; clear edx


        mov     eax, 0xB0025508         ; move least significant digits of ID# to eax
        add     eax, 0xDDDEED0F         ; add least significant digits of first string
        adc     ecx,0x0                 ;store carry
        mov     dword ptr P8Bsum, eax   ; store LSB of sum


        mov     ebx, 0xFACEC0FF; move most significant of ID# digits to ebx
        adc     ebx, 0xDDDEED0F; add scond string to first
        adc     cx, 0x0; add w / carry
        mov     dword ptr P8Bsum + 4, ebx;   store MSB of sum
        mov     P8Bcarry, cl; store carry

        nop; no op for Part B break point
    }

    // Part C adds 0xFA CE C0 FF  B0 02 55 08 
    //          to 0xEE FE ED BA  DD DE ED 0F
    //  using direct addressing
    //   and dword pointers

    // Manually calculated results: 
    // My calculated carry = 
    // My calculated sum = 0x1E9CD AEBA 8DE1 4217

    //  your properly formatted assembly language data here
    unsigned __int64 P8Cnum1 = 0xFACEC0FFB0025508; //Use your B number
    unsigned __int64 P8Cnum2 = 0xEEFEEDBADDDEED0F;
    unsigned __int64 P8Csum = 0;
    char P8Ccarry = 0;

    __asm {
        //  your syntactically correct assembly language code here
        //  column alignment markers below (to guide you)
        //      |       |               |
        sub     ecx, ecx; clear carry reg
        mov     eax, dword ptr P8Cnum1 + 0; load num1 LSB
        add     eax, dword ptr P8Cnum2 + 0; add num2 LSB to num1 LSB
        mov     dword ptr P8Csum, eax; store LSB of result

        mov     ebx, dword ptr P8Cnum1 + 4; load num1 into LSB
        adc     ebx, dword ptr P8Cnum2 + 4; add with carry P8Cnum2 + 4
        adc     cx, 0x0; store carry
        mov     dword ptr P8Csum + 4, eax; store MSB of result
        mov     P8Ccarry, cl; store carry

        nop; no op for Part C break point
    }

    // Part D adds FACE C0FF B002 5508 to 0xEEFE EDBA DDDE ED0F using direct addressing
    //   and word pointers

    // Manually calculated results: 
    // My calculated carry = 
    // My calculated sum = 

    //  your properly formatted assembly language data here
    unsigned __int64 P8Dnum1 = 0xFACEC0FFB0025508; //Use your B number
    unsigned __int64 P8Dnum2 = 0xEEFEEDBADDDEED0F;
    unsigned __int64 P8Dsum = 0;
    unsigned __int64 P8Dcarry = 0;

    __asm {
        //  your syntactically correct assembly language code here
        //  column alignment markers below (to guide you)
        //      |       |               |
        mov     eax,0x0                 ;clear eax
        mov     ebx,0x0                 ;clear ebx
        mov     ecx,0x0                 ;cler ecx
        mov     edx, 0x0                ; clear edx
        mov     edi, 0x0                ; zero carry register

// add first word
        mov     ax, word ptr P8Dnum1    ; move 5508 to axh
        add     ax, word ptr P8Dnum2    ; add ED0F to 5508
        adc     edi,0x0                 ;store carry   
        mov     word ptr P8Dsum, ax     ;store result
//add second word (with carry)
        mov     bx, word ptr P8Dnum1 +2 ; move B002h to ax
        add     bx, word ptr P8Dnum2+2  ; add DDDEh to B002
        adc     word ptr P8Dsum+2, bx     ;store result
        adc     edi, 0x0                ;store carry
//add third word (with carry)
        mov     cx, word ptr P8Dnum1 + 4; move C0FFh to ax
        add     cx, word ptr P8Dnum2 + 4; add EDBAh to C0FFh
        adc     word ptr P8Dsum+4,cx     ;add cx result w/carry to sum
        adc     edi,0x0                  ;store carry
//add fourth word 
        mov     dx, word ptr P8Dnum1 + 6; move FACEh to ax
        add     dx, word ptr P8Dnum2 + 6    ; add EEFEh to FACEh
        adc     word ptr P8Dsum+6,dx        ;add dx result w/carry to sum
        mov     dword ptr P8Dcarry, edi               ;store carry
        nop; no op for Part D break point
    }
    return(0);
}
