// Grammar following MSC Z.120 I-UIT specifications

grammar Msc;

options
{
  language = C;
  k = 2;
}

@parser::includes
{
  # include "msc/all.hh"
}

mscTextualFile returns [msc::MscTextualFile* n = new msc::MscTextualFile()]:
  (
    textualMSCDocument
    (
      msc = messageSequenceChart
      { // code
        $n.push_back($msc.n);
        mscs.push_back($msc.n);
      } // !code
    )*
  )+
  { // code
    $n = new msc::MscTexutalFile($textualMSCDocument.n);
  } // !code
;

/* [Z.120] 1.4.1	-- Lexical Rules
   [Z.120] 1.4.2	-- Visibility and Naming Rules
   [Z.120] 1.4.3	-- Comment */

end:
  (comment)? ";"! ;

comment returns [msc::String str = ""]:
  'comment' CharacterString { $str = $CharacterString.str; }
;

textDefinition returns [msc::String str = ""]:
  'text' CharacterString end { $str = $CharacterString.str); }
;

/* [Z.120] 1.4.4	-- Drawing Rules
   [Z.120] 1.4.5	-- Paging of MSCs
   [Z.120] 1.5		-- Message Sequence Chart document */

textualMSCDocument returns [msc::TextualMscDocument* n]:
  documentHead textualDefiningPart textualUtilityPart
  {
    $n = new msc::TextualMscDocument($documentHead.n
                                     $textualDefiningPart.n,
                                     $textualUtilityPart.n);
  }
;

/*x Several changes, details see below */
documentHead
	:   MSCDOCUMENT! instanceKind ( RELATED! TO! sdlReference )?
		(
			{ msc96==true }? ";"! /*x <end> -> ";", D3 F */
		|   ( inheritance )? ";"! /*x <end> -> ";", D3 F */
			( parenthesisDeclaration )? /*x D3 C */
			dataDefinition  /*x D3 C */
			/*x In MSC2000 this is optional, but dataDefinition can already be empty */
			usingClause
			containingClause
			messageDeclClause
			timerDeclClause
		)
		{ ## = #([DocumentHead], ##); }
	;


textualDefiningPart
	: ( definingMscReference )* ;

textualUtilityPart
	: UTILITIES! ( containingClause )? ( definingMscReference )*
        { ## = #([TextualUtilityPart], ##); }
    ;


definingMscReference
	: REFERENCE! ( virtuality )? mscName
        { ## = #([DefiningMscReference], ##); }
    ;


virtuality
	: VIRTUAL | REDEFINED | FINALIZED ;

/*x <end>->";", D3 F */
usingClause
	: ( USING! instanceKind ";"! )*
        { ## = #([UsingClause], ##); }
    ;


containingClause
	: ( INST! instanceItem )+
		{ ## = #([ContainingClause], ## ); }
	;

/*x <end>->";", D3 F */
instanceItem!
	: in:instanceName ( ":" ik:instanceKind )? ( i:inheritance )?
		( d:decomposition )?
		( ddl:dynamicDeclList | ";"! )
		{ ## = #( in, ik, i, d, ddl ); }
	;

inheritance
	: INHERITS! instanceKind
        { ## = #([Inheritance], ## ); }
    ;

/*x <end>->";", D3 F */
messageDeclClause
	: ( MSG! messageDecl ";"! )*
        { ## = #([MessageDeclClause], ##); }
    ;

/*x <end>->";", D3 F */
timerDeclClause
	: ( TIMER! timerDecl ";"! )*
        { ## = #([TimerDeclClause], ##); }
    ;

sdlReference
	: sdlDocumentIdentifier ;

identifier
	: ( Qualifier )? Name ;

/*x rule qualifier moved to Lexer, because Lexer needs "<<"-context
  information
qualifier
	: QualifierLeft Text QualifierRight ;
*/

/* [Z.120] 1.6		-- Basic MSC
   [Z.120] 1.6.1	-- Message Sequence Chart */

/*x Note: D3 F suggests to replace the <end> by ";" */
messageSequenceChart
	: ( virtuality )? MSC! mscHead ( msc | hmsc ) ENDMSC! end!
		{ ## = #( #[MessageSequenceChart], ## ) ; }
	;

msc	: mscBody ;

mscHead
	: mscName ( mscParameterDecl )? ( timeOffset )? end
		( mscInstInterface )? mscGateInterface
		{ ## = #( #[MscHead], ## ) ; }
	;

/*x rev 1 */
/* XXX Helmut: old rule allowed to have an empty mscParmDeclList, check this */
mscParameterDecl
    : "("! mscParmDeclList ")"!
    ;

/*x rev 1 */
/*x Note: D3 F suggests to replace the <end> by ";" */
mscParmDeclList
    : mscParmDeclBlock ( end mscParmDeclList )?
    ;

/*x rev 1 */
mscParmDeclBlock
    : dataParameterDecl
    | instanceParameterDecl
    | messageParameterDecl
    | timerParameterDecl
    ;

/*x <end> removed, D3 E */
instanceParameterDecl
	: INST! instanceParmDeclList
		{ ## = #( #[InstanceParameterDeclaration], ## ) ; }
	;

instanceParmDeclList
	: instanceParameterName ( ":"! instanceKind )?
		( ","! instanceParmDeclList )?
	;

/*x rev 1 */
instanceParameterName
	: instanceName ;


messageParameterDecl
	: MSG! messageParmDeclList
		{ ## = #( #[MessapeParameterDeclaration], ## ) ; }
	;

messageParmDeclList
	: messageDeclList ;

timerParameterDecl
	: TIMER! timerParmDeclList
		{ ## = #( #[TimerParameterDeclaration], ## ) ; }
	;

timerParmDeclList
	: timerDeclList ;

mscInstInterface
	: containingClause ;

instanceKind!
	: ( ( kindDenominator identifier ) => kd:kindDenominator )? i:identifier
		{ ## = #( #[InstanceKind], i, kd ) ; }
	;

/*x rev 1*/
kindDenominator
	: kindName ;

mscGateInterface
	: ( mscGateDef )* ;

mscGateDef
	: GATE! /*X Helmut: Check AST for this */
		( ( ( gateName )? ( IN | OUT ) ) => mscGate
		| ( ( gateName )? ( CALL | RECEIVE ) ) => methodCallGate
		| replyGate
		| createGate | orderGate ) end
	;

mscGate	: ( ( gateName )? OUT ) => defInGate
	| ( ( gateName )? IN ) => defOutGate
	;

methodCallGate
	: ( ( gateName )? RECEIVE ) => defOutCallGate
	| ( ( gateName )? CALL ) => defInCallGate
	;

replyGate
	: ( ( gateName )? REPLYIN ) => defOutReplyGate
	| ( ( gateName )? REPLYOUT ) => defInReplyGate
	;

createGate
	: defCreateInGate | defCreateOutGate ;

orderGate
	: defOrderInGate | defOrderOutGate ;

mscBody
	: ( mscStatement )*
		{ ## = #( #[MscBody], ## ) ; }
	;

/*x added msc92InstanceHeadStatement for MSC92/96 backward compat. */
mscStatement
	: textDefinition | eventDefinition
    | {msc96==true}? msc92EventDefinition
    ;

/*x added msc92EventDefinition for MSC92/96 backward compat. */
msc92EventDefinition!
    : INSTANCE in:instanceName
        ieh:msc92InstanceHeadStatement iel:instanceEventList
        { ## = #( #[EventDefinition] , #( #[InstanceNames], in),
            #( #[InstanceEvents], ieh, iel) ) ; }
    ;

/*x added msc92InstanceHeadStatement for MSC92/96 backward compat. */
msc92InstanceHeadStatement
    :   ( ( ":"! )? instanceKind )? ( decomposition )? end
        { ## = #( #[InstanceHead], ## ) ; }
    ;

eventDefinition!
 	: ( instanceName ":" instanceEventList ) =>
		in:instanceName ":" iel:instanceEventList
		{ ## = #( #[EventDefinition], #( #[InstanceNames], in ),
            #( #[InstanceEvents], iel ) ) ; }
	| inl:instanceNameList ":" miel:multiInstanceEventList
		{ ## = #( #[EventDefinition],
            #( #[InstanceNames], inl ),
            #( #[InstanceEvents], miel ) ) ; }
	;

/*x syntactic predicate needed due to nondeterminism of Z.120 11/99 rule */
instanceEventList
 	: instanceEvent ( ( instanceEvent ) => instanceEventList )? ;

instanceEvent
	: orderableEvent | nonOrderableEvent ;

/*x <end>->";", D3 F */
orderableEvent!
    :
		( ( {msc96==true}? |  LABEL )
			lbl:( evn: eventName { #lbl = #([Label], evn); } )
			( {msc96==true}? |  end ) )?
		/*x MSC2000 has 'LABEL' and 'end', while MSC96 has not */
        (
			(messageEvent) => r1:messageEvent { ## = #r1;}
		| ime:incompleteMessageEvent {## = #ime; }
		| ( methodCallEvent ) => mce:methodCallEvent {## = #mce; }
		| imce:incompleteMethodCallEvent {## = #imce; }
		| c:create {## = #c; }
		| t:timerStatement {## = #t; }
		| a:action  {## = #a; }
		)
        ( BEFORE bodl:orderDestList { #bodl->setText("before"); })? /*XXX Better add an AST node for this */
        ( AFTER aodl:orderDestList  { #bodl->setText("after"); } )? /*XXX Better add an AST node for this */
        en:end
        time:( TIME! tdl:timeDestList ";"! )? /*XXX Better add an AST node for this */
        {
            astFactory.addASTChild(currentAST, #lbl);
            astFactory.addASTChild(currentAST, #bodl);
            astFactory.addASTChild(currentAST, #aodl);
            astFactory.addASTChild(currentAST, #tdl);
            astFactory.addASTChild(currentAST, #en);
        }
    ;

orderDestList
	: orderDest ( ","! orderDestList )?
		{ ## = #([OrderDestList], ##); }
    ;

/*x rule differs from Z.120 rev 1 for separate AST-Nodes on the same level */
timeDestList
	: timeDestination (","! timeDestList )?

	;

timeDestination
	: ( timeDest )? timeInterval
		{ ## = #([TimeDest], ##); }
		/*x rule differs from Z.120 11/99, (timeDest)? and */
		/*x timeInterval are transposed. D3 */
	;

/*x rev. 1 */
timeDest /*X Helmut: Check AST for this */
	: eventName |  ( TOP { ## = #[Top]; } | BOTTOM { ## = #[Bottom]; } ) (  referenceIdentification | labelName );

/* orderableEvents are terminated in rule orderableEvents by and end or ";", nonOrderableEvents are terminated in later rules */
nonOrderableEvent
	: startMethod | endMethod | startSuspension | endSuspension
	| startCoregion | endCoregion | sharedCondition
	| sharedMSCReference | sharedInlineExpr
	| instanceHeadStatement | instanceEndStatement | stop
	;

instanceNameList
	: instanceName ( ","! instanceName )*
	| ALL { ## = #[Name,"all"] ; }
	;

// original Z.120 11/99 rule:
// multiInstanceEventList
//	: ( multiInstanceEvent )+ ;
/*x syntactic predicate needed due to nondeterminism of Z.120 11/99 rule above*/
multiInstanceEventList
 	: multiInstanceEvent
		( ( multiInstanceEvent ) => multiInstanceEventList )?
	;

multiInstanceEvent
	: condition | mscReference | inlineExpr ;

/* [Z.120] 1.6.2	-- Instance */

instanceHeadStatement
	: INSTANCE! ( instanceKind )? ( decomposition )? end
		{ ## = #( #[InstanceHead], ## ) ; }
	;

instanceEndStatement
	: ENDINSTANCE! end
		{ ## = #( #[InstanceEnd], ## ) ; }
	;

/* [Z.120] 1.6.3	-- Message */

messageEvent
	: messageOutput | messageInput ;

messageOutput
	: OUT! msgIdentification TO! inputAddress
		{ ## = #( #[MessageOutput], ## ) ; }
	;

messageInput
	: IN! msgIdentification FROM! outputAddress
		{ ## = #( [MessageInput], ## ) ; }
	;

incompleteMessageEvent
	: incompleteMessageOutput | incompleteMessageInput ;

incompleteMessageOutput
	: OUT! msgIdentification TO! LOST! ( inputAddress )?
		{ ## = #( [IncompleteMessageOutput], ## ) ; }
	;

incompleteMessageInput
	: IN! msgIdentification FROM! FOUND! ( outputAddress )?
		{ ## = #( [IncompleteMessageInput], ## ) ; }
	;

msgIdentification
	: messageName ( ","! messageInstanceName )?
		( "("! parameterList ")"! )?
		{ ## = #( #[Message], ## ) ; }
	;

outputAddress
	: ( instanceName
		| ( ENV | referenceIdentification ) ( VIA gateName )? )
		{ ## = #( #[OutputAddress], ## ) ; }
	;

referenceIdentification
	: REFERENCE! mscReferenceIdentification /*x Helmut: Check AST for this */
	| INLINE! inlineExprIdentification
	;

inputAddress
	: ( instanceName
		| ( ENV | referenceIdentification ) ( VIA gateName )? )
		{ ## = #( #[InputAddress], ## ) ; }
	;

/* [Z.120] 1.6.4	-- Control Flow */

methodCallEvent
	: callOut | callIn | replyOut | replyIn ;

callOut
	: CALL! msgIdentification TO! inputAddress
		{ ## = #( #[CallOut], ## ) ; }
	;

callIn
	: RECEIVE! msgIdentification FROM! outputAddress
		{ ## = #( #[CallIn], ## ) ; }
	;

replyOut
	: REPLYOUT! msgIdentification TO! inputAddress
		{ ## = #( #[ReplyOut], ## ) ; }
	;

replyIn
	: REPLYIN! msgIdentification FROM! outputAddress
		{ ## = #( #[ReplyIn], ## ) ; }
	;

incompleteMethodCallEvent
	: incompleteCallOut | incompleteCallIn |
		incompleteReplyOut | incompleteReplyIn
	;

incompleteCallOut
	: CALL! msgIdentification TO! LOST! ( inputAddress )?
		{ ## = #( #[IncompleteCallOut], ## ) ; }
	;

incompleteCallIn
	: RECEIVE! msgIdentification FROM! FOUND! ( outputAddress )?
		{ ## = #( #[IncompleteCallIn], ## ) ; }
	;

incompleteReplyOut
	: REPLYOUT! msgIdentification TO! LOST! ( inputAddress )?
		{ ## = #( #[IncompleteReplyOut], ## ) ; }
	;

incompleteReplyIn
	: REPLYIN! msgIdentification FROM! FOUND! ( outputAddress )?
		{ ## = #( #[IncompleteReplyIn], ## ) ; }
	;

startMethod
	: METHOD! end
		{ ## = #( #[StartMethod], ## ) ; }
	;

endMethod
	: ENDMETHOD! end
		{ ## = #( #[EndMethod], ## ) ; }
	;

startSuspension
	: SUSPENSION! end
		{ ## = #( #[StartSuspension], ## ) ; }
	;

endSuspension
	: ENDSUSPENSION! end
		{ ## = #( #[EndSuspension], ## ) ; }
	;

/* [Z.120] 1.6.5	-- Environment and Gates */

actualOutGate
	: ( gateName )? OUT! msgIdentification TO! inputDest
		{ ## = #( #[OutGate], ## ) ; }
	;

actualInGate
	: ( gateName )? IN! msgIdentification FROM! outputDest
		{ ## = #( #[InGate], ## ) ; }
	;

inputDest
	: LOST! ( ( inputAddress ) => inputAddress )? | inputAddress ;

outputDest
	: FOUND! ( ( outputAddress ) => outputAddress )? | outputAddress ;

defInGate
	: ( gateName )? OUT! msgIdentification TO! inputDest
		{ ## = #( #[DefInGate], ## ) ; }
	;

defOutGate
	: ( gateName )? IN! msgIdentification FROM! outputDest
		{ ## = #( #[DefOutGate], ## ) ; }
	;

actualOrderOutGate
	: gateName BEFORE! orderDest
		{ ## = #( #[OrderOutGate], ## ) ; }
	;

orderDest
	: eventName | ( ENV | referenceIdentification ) VIA gateName ;

actualOrderInGate
	: gateName
		( AFTER! orderDest )?
		{ ## = #( #[OrderInGate], ## ) ; }
	;

defOrderInGate
	: gateName BEFORE! orderDest
		{ ## = #( #[DefOrderInGate], ## ) ; }
	;

defOrderOutGate
	: gateName
		( AFTER! orderDestList )?
		{ ## = #( #[DefOrderOutGate], ## ) ; }
	;

actualCreateOutGate
	: CREATE! OUT! createGateIdentification CREATE! createTarget
		{ ## = #( #[CreateOutGate], ## ) ; }
	;

actualCreateInGate
	: CREATE! IN! createGateIdentification
		{ ## = #( #[CreateInGate], ## ) ; }
	;

createTarget
	: instanceName | ( ENV | referenceIdentification ) ( VIA gateName )? ;

defCreateInGate
	: CREATE! OUT! ( createGateIdentification )?
		CREATE! createTarget
        { ## = #( #[DefCreateInGate], ## ) ; }
	;

defCreateOutGate
	: CREATE! IN! createGateIdentification
        { ## = #( #[DefCreateOutGate], ## ) ; }
	;

inlineOutGate
	: defOutGate
		( EXTERNAL! OUT! msgIdentification TO! inputDest )?
        { ## = #( #[InlineOutGate], ## ) ; }
	;

inlineInGate
	: defInGate
		( EXTERNAL! IN! msgIdentification FROM! outputDest )?
        { ## = #( #[InlineInGate], ## ) ; }
	;

inlineOutCallGate
	: defOutCallGate
		( EXTERNAL! CALL! msgIdentification TO! inputDest )?
        { ## = #( #[InlineOutCallGate], ## ) ; }
	;

inlineInCallGate
	: defInCallGate
		( EXTERNAL! RECEIVE! msgIdentification FROM! outputDest )?
        { ## = #( #[InlineInCallGate], ## ) ; }
	;

inlineOutReplyGate
	: defOutReplyGate
		( EXTERNAL! REPLYOUT! msgIdentification TO! inputDest )?
        { ## = #( #[InlineOutReplyGate], ## ) ; }
	;

inlineInReplyGate
	: defInReplyGate
		( EXTERNAL! REPLYIN! msgIdentification FROM! outputDest )?
        { ## = #( #[InlineInReplyGate], ## ) ; }
	;

inlineCreateOutGate
	: defCreateOutGate
        ( EXTERNAL! create )?
        { ## = #( #[InlineCreateOutGate], ## ) ; }
	;

inlineCreateInGate:
  defCreateInGate
  ('external' 'create' 'fromt' createSource )?
  { // code
    // ## = #( #[InlineCreateInGate], ## ) ;
  } // !code
;

createSource:
  instanceName
  | ('env' | referenceIdentification) ('via' createGateIdentification)?
;

inlineOrderOutGate:
  gateName (('after' orderDestList)? 'external' 'before' orderDest)?
  { // code
    // ## = #( #[InlineOrderOutGate], ## ) ;
  } // !code
;

inlineOrderInGate:
  gateName 'before' orderDest
  ('external' ('after' orderDestList)?)?
  { // code
    // ## = #( #[InlineOrderInGate], ## ) ;
  } // !code
;

actualOutCallGate:
  gateName? 'call' msgIdentification 'to' inputDest
  { // code
    // ## = #( #[ActualOutCallGate], ## ) ;
  } // !code
;

actualInCallGate:
  gateName 'receive' msgIdentification 'from' outputDest
  { // code
    // ## = #( #[ActualInCallGate], ## ) ;
  } // !code
;

defInCallGate:
  gateName? 'call' msgIdentification 'tp' inputDest
  { // code
    // ## = #([DefInCallGate], ## );
  } // !code
;

defOutCallGate:
  gateName? 'receive' msgIdentification 'from' outputDest
  { // code
    // ## = #([DefOutCallGate], ## );
  } // !code
;

actualOutReplyGate:
  gateName? 'replyout' msgIdentification 'to' inputDest
  { // code
    // ## = #([ActualOutReplyGate], ## );
  } // !code
;

actualInReplyGate:
  gateName? 'replyin' msgIdentification 'from' outputDest
  { // code
    // ## = #([ActualInReplyGate], ## );
  } // !code
;

defInReplyGate:
  gateName? 'replyout' msgIdentification 'to' inputDest
  { // code
    // ## = #([DefInReplyGate], ## );
  } // !code
;

defOutReplyGate:
  gateName? 'replyin' msgIdentification 'from' outputDest
  { // code
    // ## = #([DefOutReplyGate], ## );
  } // !code
;

/* [Z.120] 1.6.6	-- General ordering defined in 1.6.1
   [Z.120] 1.6.7	-- Condition */

sharedCondition:
  shared? conditionIdentification shared end
  { // code
    // ## = #( #[SharedCondition], ci, s1, s2, e ) ;
  } // !code
;

conditionIdentification:
  'condition' conditionText ;

conditionText:
  (
    conditionNameList { /* ## = #( #[SettingConditionNameList], c1 ) ;*/ }
    | 'when'
    (
      conditionNameList { /*## = #( #[GuardingConditionNameList], c2 ) ;*/ }
      | '(' expression ')' { /*## = #( #[GuardingConditionExpression], e1 ) ;*/ }
    )
    | 'otherwise' { /*## = #( #[GuardingConditionNameList], #[Otherwise] ) ;*/ }
  )
;

conditionNameList:
  conditionName	(',' conditionName)*
;

shared:
  'shared' (sharedInstanceList? | 'all')
;

sharedInstanceList:
  instanceName (',' instanceName)*
;

condition:
  (shared)? conditionIdentification end
  { // code
    // ## = #( #[Condition], ci, s, e ) ;
  } // !code
;

/* [Z.120] 1.6.8	-- Timer */

timerStatement:
  starttimer | stoptimer | timeout
;

starttimer:
  'starttimer' timerName (',' timerInstanceName)? (duration)? ('(' parameterList ')')?
  { // code
    // ## = #( #[StartTimer], ## ) ;
  } // !code
;

duration:
  '[' (minDurationlimit)? (',' maxDurationlimit)? ']'
  { // code
    // ## = #( #[Duration], ## ) ;
  } // !code
;

durationlimit:
  (expressionString | 'inf')
  { // code
    // ##->setType(DurationLimit) ;
  } // !code
;

stoptimer:
  'stoptimer' timerName (',' timerInstanceName)?
  { // code
    // ## = #( #[StopTimer], ## ) ;
  } // !code
;

timeout:
  'timeout' timerName (',' timerInstanceName)?
  ('(' parameterList ')')?
  { // code
    // ## = #( #[TimeOut], ## ) ;
  } // !code
;

/* [Z.120] 1.6.9	-- Action */

action:
  'action' actionStatement
  { // code
    // ## = #( #[Action], ## ) ;
  } // !code
;

actionStatement:
  (informalAction | dataStatementList)
  { // code
    // ##->setType(ActionName);
  } // !code


informalAction:
  CharacterString
;

/* [Z.120] 1.6.10	-- Instance creation */

create:
  'create' instanceName ('(' parameterList ')')?
  { // code
    // ## = #( #[InstanceCreation], ## ) ;
  } // !code
;

/* [Z.120] 1.6.11	-- Instance stop */

stop:
  'stop' end
  { // code
    // ## = #( #[InstanceStop], ## ) ;
  } // !code
;

/* [Z.120] 1.7		-- Data Concepts
   [Z.120] 1.7.1	-- Introduction
   [Z.120] 1.7.2	-- Syntax interface to external data languages */

parenthesisDeclaration:
  'parenthesis' parDeclList end
  { // code
    // ## = #( #[ParenthesisDeclaration], ## ) ;
  } // !code
;

parDeclList:
  (nestableParPair | nonNestableParPair | equalParDecl | escapeDecl)
  (parDeclList)?
;

nestableParPair:
  'nestable' pairParList end
  { // code
    // ## = #( #[NestableParPair], ## ) ;
  } // !code
;

nonNestableParPair:
  'nonnestable' pairParList end
  { // code
    // ## = #( #[NonNestableParPair], ## );
  } // !code
;

/*x rev 1 */
equalParDecl:
  'equalpar' equalParList end
  { // code
    // ## = #( #[EqualParDelim], ## ) ;
  } // !code
;

escapeDecl:
  'escape' escapechar
  { // code
    // ## = #( #[EscapeDecl], ## ) ;
  } // !code
;

pairParList:
  pairPar (',' pairPar)*
;

pairPar:
  delim openPar delim closePar delim
;

equalParList:
  equalPar (',' equalPar)*
;

delim:
  Alphanumeric
  | Misc
  | Special
  | FullStop
  | Underline
;

openPar:
  par
;

closePar:
  par
;

equalPar:
  par
;

/*x CharacterString as in Z.120 11/99 & rev 1 is wrong,  because we have already */
/*x the delims as apostrophe, so Text would be a solution. */
/*x But Text doesn't work either, because it is not a LexicalUnit and */
/*x thus no TokenType which can be matched in this Parser! */
/*x Thus we use currently Name | National | Special | Misc ... */
par:
  Name | National | Special | Misc
;


/*x CharacterString as in Z.120 11/99 & rev 1 is wrong,  because we have already */
/*x the delims as apostrophe, so Text would be a solution. */
/*x But Text doesn't work either, because it is not a LexicalUnit and */
/*x thus no TokenType which can be matched in this Parser! */
/*x Thus we use currently Name | National | Special | Misc ... */
escapechar:
  delim (Name | National | Special | Misc ) delim
;

/* [Z.120] 1.7.3	-- Semantic interface to external data languages
   [Z.120] 1.7.4	-- Declaring data */

messageDeclList:
  messageDecl end (messageDeclList)?
;

messageDecl:
  messageNameList (':' '(' typeRefList ')')?
  { // code
    // ## = #( mnl, trl );
  } // !code
;

messageNameList:
  messageName (',' messageNameList)?
;

timerDeclList:
  timerDecl end (timerDeclList)?
;

timerDecl:
  timerNameList (duration)? (':' '(' typeRefList ')')?
  { // code
    // ## = #( tnl, d, trl ) ;
  } // !code
;

timerNameList:
  timerName (',' timerName)*
;

typeRefList:
  typeRefString (',' typeRefString)*
;

dynamicDeclList:
  'variables' variableDeclList end
  { // code
    // ## = #( #[DynamicDeclarationList], ##);
  } // !code
;

variableDeclList:
  variableDeclItem ((end variableDeclItem) => end variableDeclList)?
;

variableDeclItem:
  variableList ':' typeRefString
;

variableList:
  variableString (',' variableString)*
;

dataDefinition:
  ('language' dataLanguageName end)?
  (wildcardDecl)?
  ('data' dataDefinitionString end)?
  { // code
    // ## = #( #[DataDefinition], ## ) ;
  } // !code
;

wildcardDecl:
  'wildcards' variableDeclList
;

/* [Z.120] 1.7.5	-- Static Data */

dataParameterDecl:
  ('variables')? variableDeclList
;

actualDataParameters:
  ('variables')? actualDataParameterList
;

actualDataParameterList:
  expressionString (',' expressionString)*;

/* [Z.120] 1.7.6	-- Dynamic Data
   [Z.120] 1.7.7	-- Bindings */

binding:
  leftBinding | rightBinding
;

leftBinding:
  pattern leftBindSymbol expression
;

leftBindSymbol:
  ':='
;

rightBinding:
  expression rightBindSymbol pattern
;

rightBindSymbol:
  '=:'
;

expression:
  expressionString
;

pattern:
  variableString | wildcard
;

wildcard:
  wildcardString
;

/* [Z.120] 1.7.8	-- Data in message and timer parameters */

parameterList:
  parameterDefn (',' parameterList)*
  { // code
    // ## = #( #[ParameterList], ## );
  } // !code
;

parameterDefn:
  (binding | expression | pattern)
;

/* [Z.120] 1.7.9	-- Data in instance creation parameters
   [Z.120] 1.7.10	-- Data in action boxes */

dataStatementList:
  dataStatement (',' dataStatement)*
;

dataStatement:
  defineStatement | undefineStatement | binding
;

defineStatement:
  'def' variableIdentifier
;

undefineStatement:
  'undef' variableIdentifier
;

/* [Z.120] 1.7.11	-- Assumed Data Types
   [Z.120] 1.8		-- Time Concepts
   [Z.120] 1.8.1	-- Timed Semantics
   [Z.120] 1.8.2	-- Relative Timing
   [Z.120] 1.8.3	-- Absolute Timing
   [Z.120] 1.8.4	-- Time Domain
   [Z.120] 1.8.5	-- Static and Dynamic Time Variables
   [Z.120] 1.8.6	-- Time Offset */

timeOffset:
  'offset' timeExpression
  { // code
    // ## = #( #[TimeOffset], ## ) ;
  } // !code
;

/* [Z.120] 1.8.7	-- Time Points, Measurements, and Intervals
   [Z.120] 1.8.8	-- Time Points */

timePoint:
  (AbsTimeMark)? timeExpression
  { // code
    // ## = #( #[TimePoint], ## ) ;
  } // !code
;

/* [Z.120] 1.8.9	-- Measurements */

measurement:
  relMeasurement
  | absMeasurement
;

relMeasurement:
  '&' timePattern
  { // code
    // ## = #( #[RelTimeMeasurement], ## );
  } // !code
;

absMeasurement:
  '@' timePattern
  { // code
    // ## = #(#[AbsTimeMeasurement], ##) ;
  } // !code
;

/* [Z.120] 1.8.10	-- Time Interval */

timeInterval:
  (intervalLabel)? singularTime
  | (intervalLabel)? boundedTime
  (measurement)?
;

intervalLabel:
  'int_boundary' intervalName
;

singularTime:
  '[' timePoint ']'
  { // code
    // ## = #(#[SingularTime], ##);
  } // !code
  | measurement
;

boundedTime:
  (AbsTimeMark)?
  (LeftOpen { /*#l = #lo ;*/ } | LeftClosed { /*#l = #lc ;*/ })
  (timePoint  { /* #lb = #([LowerBound], tp1 );*/ })?
  ','
  (timePoint  { /*#ub = #([UpperBound], tp2 );*/ })?
  (RightOpen { /*#r = #ro ;*/ } | rc:RightClosed { /*#r = #rc ;*/ } )
  { // code
    // ## = #(#[BoundedTime], atm, l, lb, ub, r );
  } // !code
;

/* [Z.120] 1.9		-- Structural Concepts
   [Z.120] 1.9.1	-- Coregion */

startCoregion:
  'concurrent' end
  { // code
    // ## = #( #[StartCoregion], ## ) ;
  } // !code
;

endCoregion:
  'endconcurrent' end
  { // code
    // ## = #( #[EndCoregion], ## ) ;
  } // !code
;

/* [Z.120] 1.9.2	-- Inline expression */

sharedInlineExpr:
  (extraGlobal)? (sharedLoopExpr | sharedOptExpr | sharedAltExpr | sharedSeqExpr
  | sharedParExpr | sharedExcExpr)
  (
    'time' timeInterval end
    { // code
      // #time = #([Time], ti, e1);
    } // !code
  )?
  (
    'top' timeDestList end
    { // code
      // #top = #([Top], ttdl, e2);
    } // !code
  )?
  (
    'bottom' timeDestList end
    { // code
      // #bottom = #([Bottom], btdl, e3);
    } // !code
  )?
  { // code
    // ## = #( #[SharedInlineExpr], ##, time, top, bottom );
  } // !code
;

extraGlobal:
  'external';

sharedLoopExpr:
  'loop' (loopBoundary)? 'begin' (inlineExprIdentification)? shared end
  (inlineGateInterface)?
  (
    instanceEventList
    { // code
      // astFactory.addASTChild(currentAST, #( [InstanceEventList], iel) );
    } // !code
  )?
  'loop' 'end' end
  { // code
    // ## = #( #[SharedLoopExpr], ## );
  } // !code
;

sharedOptExpr:
  'opt' 'begin' (inlineExprIdentification)? shared end
  (inlineGateInterface)?
  (
    instanceEventList
    { // code
      //  astFactory.addASTChild(currentAST, #( [InstanceEventList], iel) );
    } // !code
  )?
  'opt' 'end' end
  { // code
    // ## = #( #[SharedOptExpr], ## );
  } // !code
;

sharedExcExpr:
  'exc' 'begin' (inlineExprIdentification)? shared end
  (inlineGateInterface)?
  (
    instanceEventList
    { // code
      // astFactory.addASTChild(currentAST, #( [InstanceEventList], iel) );
    } // !code
  )?
  'exc' 'end' end
  { // code
    // ## = #( #[SharedExcExpr], ## );
  } // !code
;

sharedAltExpr:
  'alt' 'begin' (inlineExprIdentification)? shared end
  (inlineGateInterface)?
  (
    instanceEventList
    { // code
      // astFactory.addASTChild(currentAST, #( [InstanceEventList], iel) );
    } // !code
  )?
  (
    'alt' end (inlineGateInterface)?
	(
      instanceEventList
      { // code
        // astFactory.addASTChild(currentAST, #( [InstanceEventList], iel2) );
      } // !code
    )?
  )*
  'alt' 'end' end
  { // code
    // ## = #( #[SharedAltExpr], ## );
  } // !code
;

sharedSeqExpr:
  'seq' 'begin' (inlineExprIdentification)? shared end
  (inlineGateInterface)?
  (
    instanceEventList
    { // code
      // astFactory.addASTChild(currentAST, #( [InstanceEventList], iel) );
    } // !code
  )?
  (
    'seq' end (inlineGateInterface)?
    (
      instanceEventList
      { // code
        // astFactory.addASTChild(currentAST, #( [InstanceEventList], iel2) );
      } // !code
    )?
  )*
  'seq' 'end' end
  { // code
    // ## = #( #[SharedSeqExpr], ## );
  } // !code
;

sharedParExpr:
  'par' 'begin' (inlineExprIdentification)? shared end
  (inlineGateInterface)?
  (
    instanceEventList
    { // code
      // astFactory.addASTChild(currentAST, #( [InstanceEventList], iel) );
    } // !code
  )?
  (
    'par' end (inlineGateInterface)?
    (
      instanceEventList
      { // code
        //  astFactory.addASTChild(currentAST, #( [InstanceEventList], iel2) );
      } // !code
    )?
  )*
  'par' 'end' end
  { // code
    // ## = #( #[SharedParExpr], ## );
  } // !code
;

inlineExpr:
  (extraGlobal)? (loopExpr | optExpr | altExpr | seqExpr | parExpr | excExpr)
  ('time' timeInterval end { /*#time = #([Time], ti, e1);*/ })?
  ('top' timeDestList end {/*#top = #([Top], ttdl, e2);*/ })?
  ('bottom' timeDestList end {/*#bottom = #([Bottom], btdl, e3);*/})?
  { // code
    // ## = #( #[InlineExpr], ##, time, top, bottom );
  } // !code
;

loopExpr:
  'loop' (loopBoundary)? 'begin'
  (inlineExprIdentification)? end
  (inlineGateInterface)? mscBody
  'loop' 'end' end
  { // code
    // ## = #( #[LoopExpr], ## );
  } // !code
;

optExpr:
  'opt' 'begin' (inlineExprIdentification)? end
  (inlineGateInterface)? mscBody
  'opt' 'end' end
  { // code
    // ## = #( #[OptExpr], ## ) ;
  } // !code
;

excExpr:
  'exc' 'begin' (inlineExprIdentification)? end
  (inlineGateInterface)? mscBody
  'exc' 'end' end
  { // code
    // ## = #( #[ExcExpr], ## ) ;
  } // code
;


altExpr:
  'alt' 'begin' (inlineExprIdentification)? end
  (inlineGateInterface)? mscBody
  ('alt' end (inlineGateInterface)? mscBody)*
  'alt' 'end' end
  { // code
    //  ## = #( #[AltExpr], ## ) ;
  } // !code
;

seqExpr:
  'seq' 'begin' (inlineExprIdentification)? end
  (inlineGateInterface)? mscBody
  ('seq' end (inlineGateInterface)? mscBody)*
  'seq' 'end' end
  { // code
    // ## = #( #[SeqExpr], ## ) ;
  } // !code
;

parExpr:
  'par' 'begin' (inlineExprIdentification)? end
  (inlineGateInterface)? mscBody
  ('par' end (inlineGateInterface)? mscBody)*
  'par' 'end' end
  { // code
    //  ## = #( #[ParExpr], ## ) ;
  } // !code
;

loopBoundary:
  '<' infNatural (',' infNatural)? '>'
  { // code
    // ## = #( #[LoopBoundary], ## ) ;
  } // !code
;

infNatural:
  'inf' | expression
;

inlineExprIdentification:
  inlineExprName
;

inlineGateInterface:
  ('gate' inlineGate end)+
  { // code
    // ## = #( #[InlineGateInterface], ## ) ;
  } // !code
;

inlineGate:
  inlineOutGate
  | inlineInGate
  | inlineCreateOutGate
  | inlineCreateInGate
  | inlineOutCallGate
  | inlineInCallGate
  | inlineOutReplyGate
  | inlineInReplyGate
  | inlineOrderOutGate
  | inlineOrderInGate
;

/* [Z.120] 1.9.3	-- MSC reference */

sharedMSCReference:
  'reference' (mscReferenceIdentification ':')?
  mscRefExpr shared end
  ('time' timeInterval end { /*#time = #([Time], ti, e1); */ })?
  ('top' timeDestList end {/*#top = #([Top], ttdl, e2);*/})?
  ('bottom' timeDestList end {/*#bottom = #([Bottom], btdl, e3);*/})?
  referenceGateInterface
  { // code
    //  ## = #( #[SharedMscReference], ##, time, top, bottom );
  } // !code
;

mscReference:
  'reference' (mscReferenceIdentification ':')?
  mscRefExpr end
  ('time' timeInterval end { /*#time = #([Time], ti, e1);*/ })?
  ('top' timeDestList end { /*#top = #([Top], ttdl, e2);*/ })?
  ('bottom' timeDestList end { /*#bottom = #([Bottom], btdl, e3);*/ })?
  referenceGateInterface
  { // code
    //  ## = #( #[MscReference], ##, time, top, bottom );
  } // !code
;

mscReferenceIdentification:
  mscReferenceName
;

mscRefExpr:
  mscRefParExpr ('alt' mscRefParExpr)*
  { // code
    // ## = #( #[MscRefExpr], ## );
  } // !code
;

mscRefParExpr:
  mscRefSeqExpr ('par' mscRefSeqExpr)*
  { // code
    // ## = #( #[MscRefParExpr], ## ) ;
  } // !code
;

mscRefSeqExpr:
  mscRefIdentExpr ('seq' mscRefIdentExpr)*
  { // code
    // ## = #( #[MscRefSeqExpr], ## ) ;
  } // !code
;

mscRefIdentExpr:
  'loop' (loopBoundary)? mscRefIdentExpr { /* ## = #(#[Loop], ##); */ }
  | 'exc' mscRefIdentExpr { /* ## = #(#[Exc], ##); */}
  | 'opt' mscRefIdentExpr { /* ## = #(#[Opt], ##); */ }
  | 'empty' { /* ## = #(#[Empty], ##); */ }
  | (parent)* mscName (actualParameters)?
  | '(' mscRefExpr ')'
;

actualParameters:
  '(' actualParametersList ')'
;

actualParametersList:
  actualParametersBlock (end actualParametersBlock)*
;

actualParametersBlock:
  actualDataParameters
  | actualInstanceParameters
  | actualMessageParameters
  | actualTimerParameters
;

actualInstanceParameters:
  'inst' actualInstanceParmList
  { // code
    // ## = #( #[InstanceParameters], ##);
  } // !code
;

actualInstanceParmList:
  actualInstanceParameter (',' actualInstanceParameter)*
;

actualInstanceParameter:
  instanceName
;

actualMessageParameters:
  'msg' actualMessageList
  { // code
    //  ## = #( #[MessageParameters], ## );
  } // !code
;

actualMessageList:
  messageName (';' messageName)*
;

actualTimerParameters:
  'timer' actualTimerList
  { // code
    //  ## = #( #[TimerParameters], ## );
  } // !code
;

actualTimerList:
  timerName (',' timerName)*
;

parent:
  '#'
;

referenceGateInterface:
  ('gate' refGate end)*
;

refGate:
  ((gateName)? 'out') => actualOutGate
  | ((gateName)? 'in') => actualInGate
  | actualOrderOutGate
  | (gateName ('after' orderDest)? end) => actualOrderInGate
  | actualCreateOutGate
  | actualCreateInGate
  | ((gateName)? 'call') => actualOutCallGate
  | ((gateName)? 'receive') => actualInCallGate
  | ((gateName)? 'replyout') => actualOutReplyGate
  | actualInReplyGate
;

/* [Z.120] 1.9.4	-- Instance decomposition */

decomposition:
  'decomposed' (substructureReference)?
  { // code
    // ## = #( #[Decomposition], ## );
  } // !code
;

substructureReference:
  'as' messageSequenceChartName
;

/* [Z.120] 1.9.5	-- High-level MSC (HMSC) */

hmsc:
  'expr' mscExpression
  { // code
    // ## = #( #[HmscBody], ## );
  } // !code
;

mscExpression:
  start (nodeExpression | textDefinition)*
  { // code
    // ## = #( #[MscExpression], ## );
  } // !code
;

start:
  labelNameList end
;

nodeExpression:
  labelName ':' (((timeableNode | node) 'seq' '(' labelNameList ')') | 'end') end
  { // code
    // ## = #( #[NodeExpression], ## );
  } // !code
;

labelNameList:
  labelName ('alt' labelName)*
  { // code
    // ## = #( #[LabelNameList], ## );
  } // !code
;

timeableNode:
  ('(' mscRefExpr ')' | parExpression )
  (
    'time' timeInterval end
    { // code
      /*#time = #([Time], ti, e1);*/
    } // !code
  )?
  (
    'top' timeDestList end
    { // code
      // #top = #([Top], ttdl, e2);
    } // !code
  )?
  ('bottom' timeDestList end
    { // code
      // #bottom = #([Bottom], btdl, e3);
    } // !code
  )?
  { // code
    // ## = #( #[TimeableNode], ##, time, top, bottom );
  } // !code
;

node returns [msc::Node* n]:
  conditionIdentification { $n = $conditionIdentification.n; }
  | 'connect' { /* FIXME $n = new msc::Node(); */ }
;

parExpression returns [msc::ParExpression* n = new msc::ParExpression()]:
  'expr' me1 = mscExpression 'endexpr'
  { // code
    $n->push_back($me1.n);
  } // !code
  (
    'par' 'expr' me2 = mscExpression 'endexpr'
    { // code
      $n->push_back($me2.n);
    } // !code
  )*
;

/* Names : */

mscName:
  Name { ##->setType(MscName); }
;

instanceName:
  Name { ##->setType(InstanceName); }
;

actualInstanceParameterName:
  Name { ##->setType(ActualInstanceParameterName); }
;

eventName:
  Name { ##->setType(EventName); }
;

messageName:
  Name { ##->setType(MessageName); }
;

messageInstanceName:
  Name { ##->setType(InstanceName); }
;

gateName:
  Name
;

conditionName:
  ( Name | CharacterString ) { ##->setType(ConditionName); }
;

/*x for MSC96 backward compat. */
durationName:
  Name { ##->setType(DurationName); }
;

timerName:
  Name { ##->setType(TimerName); }
;

timerInstanceName:
  Name { ##->setType(InstanceName); }
;

intervalName:
  Name  { ##->setType(IntervalName); }
;

inlineExprName:
  Name  { ##->setType(InlineExprName); }
;

mscReferenceName:
  Name { ##->setType(ReferenceName); }
;

messageSequenceChartName:
  Name { ##->setType(MessageSequenceChartName); }
;

labelName:
  Name { ##->setType(LabelName); }
;

dataLanguageName:
  Name { ##->setType(DataLanguageName); } ;

kindName:
  Name { ##->setType(KindName); }
;

/* Identifiers : */

sdlDocumentIdentifier:
  identifier
;

variableIdentifier:
  identifier
;

/* Expressions : */

timeExpression:
  expression
;

/* Patterns : */

timePattern:
  pattern
;

/* Durationlimits : */

minDurationlimit:
  durationlimit
;

maxDurationlimit:
  durationlimit
;

/* Strings : */

/* The Z.120 <_expression_ string> non-terminals
   are named expressionString */

/*x deviation concerning data strings from the standard */
expressionString
	: (CharacterString | Name)
		{ ##->setType(ExpressionString); }
	;

typeRefString
	: (CharacterString | Name)
		{ ##->setType(TypeRefString); }
    ;

variableString
	: (CharacterString | Name)
		{ ##->setType(VariableString); }
    ;

dataDefinitionString
	: (CharacterString | Name)
		{ ##->setType(DataDefinitionString); }
    ;

wildcardString returns [msc::String str = ""]:
  s = (CharacterString | Name) { $str = $s.str; }
;

/* CreateGateIdentification : */

createGateIdentification:
  msgIdentification
;

