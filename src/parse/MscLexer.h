/** \file
 *  This C header file was generated by $ANTLR version 3.3 Nov 30, 2010 12:50:56
 *
 *     -  From the grammar source file : ../src/parse/Msc.g
 *     -                            On : 2011-06-04 03:52:41
 *     -                 for the lexer : MscLexerLexer *
 * Editing it, at least manually, is not wise. 
 *
 * C language generator and runtime by Jim Idle, jimi|hereisanat|idle|dotgoeshere|ws.
 *
 *
 * The lexer MscLexer has the callable functions (rules) shown below,
 * which will invoke the code for the associated rule in the source grammar
 * assuming that the input stream is pointing to a token/text stream that could begin
 * this rule.
 * 
 * For instance if you call the first (topmost) rule in a parser grammar, you will
 * get the results of a full parse, but calling a rule half way through the grammar will
 * allow you to pass part of a full token stream to the parser, such as for syntax checking
 * in editors and so on.
 *
 * The parser entry points are called indirectly (by function pointer to function) via
 * a parser context typedef pMscLexer, which is returned from a call to MscLexerNew().
 *
 * As this is a generated lexer, it is unlikely you will call it 'manually'. However
 * the methods are provided anyway.
 * * The methods in pMscLexer are  as follows:
 *
 *  -  void      pMscLexer->T__24(pMscLexer)
 *  -  void      pMscLexer->T__25(pMscLexer)
 *  -  void      pMscLexer->T__26(pMscLexer)
 *  -  void      pMscLexer->T__27(pMscLexer)
 *  -  void      pMscLexer->T__28(pMscLexer)
 *  -  void      pMscLexer->T__29(pMscLexer)
 *  -  void      pMscLexer->T__30(pMscLexer)
 *  -  void      pMscLexer->T__31(pMscLexer)
 *  -  void      pMscLexer->T__32(pMscLexer)
 *  -  void      pMscLexer->T__33(pMscLexer)
 *  -  void      pMscLexer->T__34(pMscLexer)
 *  -  void      pMscLexer->T__35(pMscLexer)
 *  -  void      pMscLexer->T__36(pMscLexer)
 *  -  void      pMscLexer->T__37(pMscLexer)
 *  -  void      pMscLexer->T__38(pMscLexer)
 *  -  void      pMscLexer->T__39(pMscLexer)
 *  -  void      pMscLexer->T__40(pMscLexer)
 *  -  void      pMscLexer->T__41(pMscLexer)
 *  -  void      pMscLexer->T__42(pMscLexer)
 *  -  void      pMscLexer->T__43(pMscLexer)
 *  -  void      pMscLexer->T__44(pMscLexer)
 *  -  void      pMscLexer->T__45(pMscLexer)
 *  -  void      pMscLexer->T__46(pMscLexer)
 *  -  void      pMscLexer->T__47(pMscLexer)
 *  -  void      pMscLexer->T__48(pMscLexer)
 *  -  void      pMscLexer->T__49(pMscLexer)
 *  -  void      pMscLexer->T__50(pMscLexer)
 *  -  void      pMscLexer->T__51(pMscLexer)
 *  -  void      pMscLexer->T__52(pMscLexer)
 *  -  void      pMscLexer->T__53(pMscLexer)
 *  -  void      pMscLexer->T__54(pMscLexer)
 *  -  void      pMscLexer->T__55(pMscLexer)
 *  -  void      pMscLexer->T__56(pMscLexer)
 *  -  void      pMscLexer->T__57(pMscLexer)
 *  -  void      pMscLexer->T__58(pMscLexer)
 *  -  void      pMscLexer->T__59(pMscLexer)
 *  -  void      pMscLexer->T__60(pMscLexer)
 *  -  void      pMscLexer->T__61(pMscLexer)
 *  -  void      pMscLexer->T__62(pMscLexer)
 *  -  void      pMscLexer->T__63(pMscLexer)
 *  -  void      pMscLexer->T__64(pMscLexer)
 *  -  void      pMscLexer->T__65(pMscLexer)
 *  -  void      pMscLexer->T__66(pMscLexer)
 *  -  void      pMscLexer->T__67(pMscLexer)
 *  -  void      pMscLexer->T__68(pMscLexer)
 *  -  void      pMscLexer->T__69(pMscLexer)
 *  -  void      pMscLexer->T__70(pMscLexer)
 *  -  void      pMscLexer->T__71(pMscLexer)
 *  -  void      pMscLexer->T__72(pMscLexer)
 *  -  void      pMscLexer->T__73(pMscLexer)
 *  -  void      pMscLexer->T__74(pMscLexer)
 *  -  void      pMscLexer->T__75(pMscLexer)
 *  -  void      pMscLexer->T__76(pMscLexer)
 *  -  void      pMscLexer->T__77(pMscLexer)
 *  -  void      pMscLexer->T__78(pMscLexer)
 *  -  void      pMscLexer->T__79(pMscLexer)
 *  -  void      pMscLexer->T__80(pMscLexer)
 *  -  void      pMscLexer->T__81(pMscLexer)
 *  -  void      pMscLexer->T__82(pMscLexer)
 *  -  void      pMscLexer->T__83(pMscLexer)
 *  -  void      pMscLexer->T__84(pMscLexer)
 *  -  void      pMscLexer->T__85(pMscLexer)
 *  -  void      pMscLexer->T__86(pMscLexer)
 *  -  void      pMscLexer->T__87(pMscLexer)
 *  -  void      pMscLexer->T__88(pMscLexer)
 *  -  void      pMscLexer->T__89(pMscLexer)
 *  -  void      pMscLexer->T__90(pMscLexer)
 *  -  void      pMscLexer->T__91(pMscLexer)
 *  -  void      pMscLexer->T__92(pMscLexer)
 *  -  void      pMscLexer->T__93(pMscLexer)
 *  -  void      pMscLexer->T__94(pMscLexer)
 *  -  void      pMscLexer->T__95(pMscLexer)
 *  -  void      pMscLexer->T__96(pMscLexer)
 *  -  void      pMscLexer->T__97(pMscLexer)
 *  -  void      pMscLexer->T__98(pMscLexer)
 *  -  void      pMscLexer->T__99(pMscLexer)
 *  -  void      pMscLexer->T__100(pMscLexer)
 *  -  void      pMscLexer->T__101(pMscLexer)
 *  -  void      pMscLexer->T__102(pMscLexer)
 *  -  void      pMscLexer->T__103(pMscLexer)
 *  -  void      pMscLexer->T__104(pMscLexer)
 *  -  void      pMscLexer->T__105(pMscLexer)
 *  -  void      pMscLexer->T__106(pMscLexer)
 *  -  void      pMscLexer->T__107(pMscLexer)
 *  -  void      pMscLexer->T__108(pMscLexer)
 *  -  void      pMscLexer->T__109(pMscLexer)
 *  -  void      pMscLexer->T__110(pMscLexer)
 *  -  void      pMscLexer->T__111(pMscLexer)
 *  -  void      pMscLexer->T__112(pMscLexer)
 *  -  void      pMscLexer->T__113(pMscLexer)
 *  -  void      pMscLexer->T__114(pMscLexer)
 *  -  void      pMscLexer->T__115(pMscLexer)
 *  -  void      pMscLexer->T__116(pMscLexer)
 *  -  void      pMscLexer->T__117(pMscLexer)
 *  -  void      pMscLexer->T__118(pMscLexer)
 *  -  void      pMscLexer->T__119(pMscLexer)
 *  -  void      pMscLexer->T__120(pMscLexer)
 *  -  void      pMscLexer->T__121(pMscLexer)
 *  -  void      pMscLexer->T__122(pMscLexer)
 *  -  void      pMscLexer->T__123(pMscLexer)
 *  -  void      pMscLexer->T__124(pMscLexer)
 *  -  void      pMscLexer->T__125(pMscLexer)
 *  -  void      pMscLexer->T__126(pMscLexer)
 *  -  void      pMscLexer->T__127(pMscLexer)
 *  -  void      pMscLexer->T__128(pMscLexer)
 *  -  void      pMscLexer->Qualifier(pMscLexer)
 *  -  void      pMscLexer->Letter(pMscLexer)
 *  -  void      pMscLexer->Decimal_Digit(pMscLexer)
 *  -  void      pMscLexer->Special(pMscLexer)
 *  -  void      pMscLexer->Name(pMscLexer)
 *  -  void      pMscLexer->Space(pMscLexer)
 *  -  void      pMscLexer->Underline(pMscLexer)
 *  -  void      pMscLexer->DecimalDigit(pMscLexer)
 *  -  void      pMscLexer->National(pMscLexer)
 *  -  void      pMscLexer->FullStop(pMscLexer)
 *  -  void      pMscLexer->UpwardArrowHead(pMscLexer)
 *  -  void      pMscLexer->CharacterString(pMscLexer)
 *  -  void      pMscLexer->Apostrophe(pMscLexer)
 *  -  void      pMscLexer->OtherCharacter(pMscLexer)
 *  -  void      pMscLexer->Overline(pMscLexer)
 *  -  void      pMscLexer->VerticalLine(pMscLexer)
 *  -  void      pMscLexer->LeftCurlyBracket(pMscLexer)
 *  -  void      pMscLexer->RightCurlyBracket(pMscLexer)
 *  -  void      pMscLexer->Misc(pMscLexer)
 *  -  void      pMscLexer->Alphanumeric(pMscLexer)
 *  -  void      pMscLexer->Tokens(pMscLexer)
 *
 * The return type for any particular rule is of course determined by the source
 * grammar file.
 */
// [The "BSD licence"]
// Copyright (c) 2005-2009 Jim Idle, Temporal Wave LLC
// http://www.temporal-wave.com
// http://www.linkedin.com/in/jimidle
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. The name of the author may not be used to endorse or promote products
//    derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef	_MscLexer_H
#define _MscLexer_H
/* =============================================================================
 * Standard antlr3 C runtime definitions
 */
#include    <antlr3.h>

/* End of standard antlr 3 runtime definitions
 * =============================================================================
 */
 
#ifdef __cplusplus
extern "C" {
#endif

// Forward declare the context typedef so that we can use it before it is
// properly defined. Delegators and delegates (from import statements) are
// interdependent and their context structures contain pointers to each other
// C only allows such things to be declared if you pre-declare the typedef.
//
typedef struct MscLexer_Ctx_struct MscLexer, * pMscLexer;



#ifdef	ANTLR3_WINDOWS
// Disable: Unreferenced parameter,							- Rules with parameters that are not used
//          constant conditional,							- ANTLR realizes that a prediction is always true (synpred usually)
//          initialized but unused variable					- tree rewrite variables declared but not needed
//          Unreferenced local variable						- lexer rule declares but does not always use _type
//          potentially unitialized variable used			- retval always returned from a rule 
//			unreferenced local function has been removed	- susually getTokenNames or freeScope, they can go without warnigns
//
// These are only really displayed at warning level /W4 but that is the code ideal I am aiming at
// and the codegen must generate some of these warnings by necessity, apart from 4100, which is
// usually generated when a parser rule is given a parameter that it does not use. Mostly though
// this is a matter of orthogonality hence I disable that one.
//
#pragma warning( disable : 4100 )
#pragma warning( disable : 4101 )
#pragma warning( disable : 4127 )
#pragma warning( disable : 4189 )
#pragma warning( disable : 4505 )
#pragma warning( disable : 4701 )
#endif

/** Context tracking structure for MscLexer
 */
struct MscLexer_Ctx_struct
{
    /** Built in ANTLR3 context tracker contains all the generic elements
     *  required for context tracking.
     */
    pANTLR3_LEXER    pLexer;


     void (*mT__24)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__25)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__26)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__27)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__28)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__29)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__30)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__31)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__32)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__33)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__34)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__35)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__36)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__37)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__38)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__39)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__40)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__41)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__42)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__43)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__44)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__45)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__46)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__47)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__48)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__49)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__50)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__51)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__52)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__53)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__54)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__55)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__56)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__57)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__58)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__59)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__60)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__61)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__62)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__63)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__64)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__65)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__66)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__67)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__68)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__69)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__70)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__71)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__72)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__73)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__74)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__75)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__76)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__77)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__78)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__79)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__80)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__81)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__82)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__83)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__84)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__85)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__86)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__87)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__88)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__89)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__90)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__91)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__92)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__93)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__94)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__95)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__96)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__97)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__98)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__99)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__100)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__101)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__102)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__103)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__104)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__105)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__106)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__107)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__108)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__109)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__110)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__111)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__112)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__113)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__114)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__115)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__116)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__117)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__118)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__119)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__120)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__121)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__122)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__123)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__124)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__125)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__126)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__127)	(struct MscLexer_Ctx_struct * ctx);
     void (*mT__128)	(struct MscLexer_Ctx_struct * ctx);
     void (*mQualifier)	(struct MscLexer_Ctx_struct * ctx);
     void (*mLetter)	(struct MscLexer_Ctx_struct * ctx);
     void (*mDecimal_Digit)	(struct MscLexer_Ctx_struct * ctx);
     void (*mSpecial)	(struct MscLexer_Ctx_struct * ctx);
     void (*mName)	(struct MscLexer_Ctx_struct * ctx);
     void (*mSpace)	(struct MscLexer_Ctx_struct * ctx);
     void (*mUnderline)	(struct MscLexer_Ctx_struct * ctx);
     void (*mDecimalDigit)	(struct MscLexer_Ctx_struct * ctx);
     void (*mNational)	(struct MscLexer_Ctx_struct * ctx);
     void (*mFullStop)	(struct MscLexer_Ctx_struct * ctx);
     void (*mUpwardArrowHead)	(struct MscLexer_Ctx_struct * ctx);
     void (*mCharacterString)	(struct MscLexer_Ctx_struct * ctx);
     void (*mApostrophe)	(struct MscLexer_Ctx_struct * ctx);
     void (*mOtherCharacter)	(struct MscLexer_Ctx_struct * ctx);
     void (*mOverline)	(struct MscLexer_Ctx_struct * ctx);
     void (*mVerticalLine)	(struct MscLexer_Ctx_struct * ctx);
     void (*mLeftCurlyBracket)	(struct MscLexer_Ctx_struct * ctx);
     void (*mRightCurlyBracket)	(struct MscLexer_Ctx_struct * ctx);
     void (*mMisc)	(struct MscLexer_Ctx_struct * ctx);
     void (*mAlphanumeric)	(struct MscLexer_Ctx_struct * ctx);
     void (*mTokens)	(struct MscLexer_Ctx_struct * ctx);
    const char * (*getGrammarFileName)();
    void            (*reset)  (struct MscLexer_Ctx_struct * ctx);
    void	    (*free)   (struct MscLexer_Ctx_struct * ctx);
        
};

// Function protoypes for the constructor functions that external translation units
// such as delegators and delegates may wish to call.
//
ANTLR3_API pMscLexer MscLexerNew         (pANTLR3_INPUT_STREAM instream);
ANTLR3_API pMscLexer MscLexerNewSSD      (pANTLR3_INPUT_STREAM instream, pANTLR3_RECOGNIZER_SHARED_STATE state);

/** Symbolic definitions of all the tokens that the lexer will work with.
 * \{
 *
 * Antlr will define EOF, but we can't use that as it it is too common in
 * in C header files and that would be confusing. There is no way to filter this out at the moment
 * so we just undef it here for now. That isn't the value we get back from C recognizers
 * anyway. We are looking for ANTLR3_TOKEN_EOF.
 */
#ifdef	EOF
#undef	EOF
#endif
#ifdef	Tokens
#undef	Tokens
#endif 
#define EOF      -1
#define T__24      24
#define T__25      25
#define T__26      26
#define T__27      27
#define T__28      28
#define T__29      29
#define T__30      30
#define T__31      31
#define T__32      32
#define T__33      33
#define T__34      34
#define T__35      35
#define T__36      36
#define T__37      37
#define T__38      38
#define T__39      39
#define T__40      40
#define T__41      41
#define T__42      42
#define T__43      43
#define T__44      44
#define T__45      45
#define T__46      46
#define T__47      47
#define T__48      48
#define T__49      49
#define T__50      50
#define T__51      51
#define T__52      52
#define T__53      53
#define T__54      54
#define T__55      55
#define T__56      56
#define T__57      57
#define T__58      58
#define T__59      59
#define T__60      60
#define T__61      61
#define T__62      62
#define T__63      63
#define T__64      64
#define T__65      65
#define T__66      66
#define T__67      67
#define T__68      68
#define T__69      69
#define T__70      70
#define T__71      71
#define T__72      72
#define T__73      73
#define T__74      74
#define T__75      75
#define T__76      76
#define T__77      77
#define T__78      78
#define T__79      79
#define T__80      80
#define T__81      81
#define T__82      82
#define T__83      83
#define T__84      84
#define T__85      85
#define T__86      86
#define T__87      87
#define T__88      88
#define T__89      89
#define T__90      90
#define T__91      91
#define T__92      92
#define T__93      93
#define T__94      94
#define T__95      95
#define T__96      96
#define T__97      97
#define T__98      98
#define T__99      99
#define T__100      100
#define T__101      101
#define T__102      102
#define T__103      103
#define T__104      104
#define T__105      105
#define T__106      106
#define T__107      107
#define T__108      108
#define T__109      109
#define T__110      110
#define T__111      111
#define T__112      112
#define T__113      113
#define T__114      114
#define T__115      115
#define T__116      116
#define T__117      117
#define T__118      118
#define T__119      119
#define T__120      120
#define T__121      121
#define T__122      122
#define T__123      123
#define T__124      124
#define T__125      125
#define T__126      126
#define T__127      127
#define T__128      128
#define Letter      4
#define Decimal_Digit      5
#define OtherCharacter      6
#define Special      7
#define Qualifier      8
#define DecimalDigit      9
#define Underline      10
#define FullStop      11
#define Name      12
#define Space      13
#define LeftCurlyBracket      14
#define VerticalLine      15
#define RightCurlyBracket      16
#define Overline      17
#define UpwardArrowHead      18
#define National      19
#define Apostrophe      20
#define Alphanumeric      21
#define CharacterString      22
#define Misc      23
#ifdef	EOF
#undef	EOF
#define	EOF	ANTLR3_TOKEN_EOF
#endif

#ifndef TOKENSOURCE
#define TOKENSOURCE(lxr) lxr->pLexer->rec->state->tokSource
#endif

/* End of token definitions for MscLexer
 * =============================================================================
 */
/** \} */

#ifdef __cplusplus
}
#endif

#endif

/* END - Note:Keep extra line feed to satisfy UNIX systems */
