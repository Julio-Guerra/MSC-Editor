// Grammar following MSC Z.120 I-UIT specifications

grammar Msc;

options
{
  language = C;
  k = 2;
}

@parser::includes
{
  #include <vector>
  #include <iostream>

  #include "msc/types.hh"
  #include "msc/all.hh"
}

@lexer::includes
{
  #include "msc/types.hh"
}


Qualifier:
  '<<'
  (
    Letter
    | Decimal_Digit
    | OtherCharacter
    | Special
    | '.'
    | '_'
    | ' '
    | '\''
  )*
  '>>'
;


Letter:
  'a'..'z' | 'A'..'Z'
;


Decimal_Digit:
   '0'..'9'
;

fragment
Special:
  '@' | '&' | '(' | ')' | '[' | ']' | '<' | '>' | '#' | ',' | ';' | ':'
;

Name:
  (Letter | DecimalDigit | Underline | FullStop)+
;

Space:
  (' ' | '\t' | '\r' | '\n')+  { $channel = HIDDEN; }
;

fragment
Underline:
  '_'
;

fragment
DecimalDigit:
  '0' .. '9'
;

National:
  '`' | '\\'
  | LeftCurlyBracket
  | VerticalLine
  | RightCurlyBracket
  | Overline
  | UpwardArrowHead
;

fragment
FullStop:
  '.'
;

fragment
UpwardArrowHead:
  '^'
;

CharacterString:
  (Apostrophe { $channel = HIDDEN; })
  ((Alphanumeric
  | OtherCharacter
  | Special
  | FullStop
  | Underline
  | Space
  | Apostrophe Apostrophe
  )*) (Apostrophe { $channel = HIDDEN; })
;

Apostrophe:
  '\''
;

OtherCharacter:
  '?' | '%' | '+' | '-' | '!' | '/' | '*' | '"' | '='
;

fragment
Overline:
  '~'
;

fragment
VerticalLine:
  '|'
;

fragment
LeftCurlyBracket:
  '{'
;

fragment
RightCurlyBracket:
  '}'
;

fragment
Misc:
  OtherCharacter | Apostrophe
;

fragment
Alphanumeric:
  Letter | DecimalDigit | National
;

mscTextualFile :
  (
    textualMSCDocument
    (
      messageSequenceChart
      {


      }
    )*
  )+
  {

  }
;

/* [Z.120] 1.4.1	-- Lexical Rules
   [Z.120] 1.4.2	-- Visibility and Naming Rules
   [Z.120] 1.4.3	-- Comment */

end:
  (comment)? ';'
;

comment:
  'comment' CharacterString {  }
;

textDefinition returns [msc::TextDefinition* n = 0]:
  'text' CharacterString end
  {
    msc::String* text = new msc::String((char*) $CharacterString.text->chars);
    $n = new msc::TextDefinition(text);
  }
;

/* [Z.120] 1.4.4	-- Drawing Rules
   [Z.120] 1.4.5	-- Paging of MSCs
   [Z.120] 1.5		-- Message Sequence Chart document */

textualMSCDocument:
  documentHead textualDefiningPart textualUtilityPart
  {
  }
;

documentHead:
  'mscdocument' instanceKind ('related' 'to' sdlReference)?
  ((inheritance)? ';'
  (parenthesisDeclaration)?
  dataDefinition
  usingClause
  containingClause
  messageDeclClause
  timerDeclClause)?
  {

  }
;

textualDefiningPart:
  (definingMscReference)*
;

textualUtilityPart:
  'utilities' (containingClause)? (definingMscReference)*
  {

  }
;


definingMscReference:
  'reference' (virtuality)? mscName
  {
  }
;

virtuality returns [msc::MessageSequenceChart::virtuality_enum n]:
  'virtual'     { $n = msc::MessageSequenceChart::VIRTUAL;   }
  | 'redefined' { $n = msc::MessageSequenceChart::REDEFINED; }
  | 'finalized' { $n = msc::MessageSequenceChart::FINALIZED; }
;

usingClause:
  ('using' instanceKind ';')*
  {

  }
;

containingClause:
  ('inst' instanceItem)+
  {

  }
;

instanceItem:
  instanceName (':' instanceKind)? (inheritance)?
  (decomposition)?
  (dynamicDeclList | ';')
  {

  }
;

inheritance:
  'inherits' instanceKind
  {

  }
;

messageDeclClause:
  ('msg' messageDecl ';')*
  {

  }
;

timerDeclClause:
  ('timer' timerDecl ';')*
  {

  }
;

sdlReference:
  sdlDocumentIdentifier
;

identifier:
  (Qualifier)? Name
;
/* [Z.120] 1.6		-- Basic MSC
   [Z.120] 1.6.1	-- Message Sequence Chart */

messageSequenceChart returns [msc::MessageSequenceChart* n = 0]:
  (v = virtuality? 'msc' mscHead (msc = bmsc | msc = hmsc) 'endmsc' end)
  { // code
    $n = new msc::MessageSequenceChart($v.text ?
                                       $v.n :
                                       msc::MessageSequenceChart::UNKNOWN,
                                       $msc.n);
  } // !code
;

bmsc returns [msc::Msc* n = 0]:
  mscBody
  { // code
    $n = new msc::BasicMsc($mscBody.n);
  } // !code
;

mscHead returns [ int n = 1, int n2 = 2 ]:
  mscName mscParameterDecl? timeOffset? end
  mscInstInterface? mscGateInterface
  {

  }
;

mscParameterDecl:
  '(' mscParmDeclList ')'
;

mscParmDeclList:
  mscParmDeclBlock (end mscParmDeclList)?
;

mscParmDeclBlock:
  dataParameterDecl
  | instanceParameterDecl
  | messageParameterDecl
  | timerParameterDecl
;

instanceParameterDecl:
  'inst' instanceParmDeclList
  {

  }
;

instanceParmDeclList:
  instanceParameterName (':' instanceKind)?
  (',' instanceParmDeclList)?
;

instanceParameterName:
  instanceName
;

messageParameterDecl:
  'msg' messageParmDeclList
  {

  }
;

messageParmDeclList:
  messageDeclList
;

timerParameterDecl:
  'timer' timerParmDeclList
  {

  }
;

timerParmDeclList:
  timerDeclList
;

mscInstInterface:
  containingClause
;

instanceKind:
  (kindDenominator)? identifier
  {

  }
;

kindDenominator:
  kindName
;

mscGateInterface:
  (mscGateDef)*
;

mscGateDef:
  'gate' (mscGate | methodCallGate | replyGate | createGate | orderGate) end
;

mscGate:
  defInGate | defOutGate
;

methodCallGate:
  defOutCallGate | defInCallGate
;

replyGate:
  defOutReplyGate
  | defInReplyGate
;

createGate:
  defCreateInGate | defCreateOutGate
;

orderGate:
  defOrderInGate | defOrderOutGate
;

mscBody returns [std::vector<msc::Statement*> n]:
  (
    mscStatement { $n.push_back($mscStatement.n); }
  )*
;

mscStatement returns [msc::Statement* n = 0]:
  textDefinition { $n = $textDefinition.n; }
  | eventDefinition { $n = $eventDefinition.n; }
;

eventDefinition returns [msc::EventDefinition* n = 0]:
  instanceName (',' instanceName)* ':' (instanceEventList | multiInstanceEventList)
  {
    //#(#[EventDefition],#( #[InstanceNames], inl),#(#[InstanceEvents],miel))
  }
;

instanceEventList:
  instanceEvent (instanceEvent)*
;

instanceEvent:
  orderableEvent | nonOrderableEvent
;

orderableEvent:
  ('label' eventName end)?
  (
    messageEvent
    | incompleteMessageEvent
    | methodCallEvent
    | incompleteMethodCallEvent
    | create
    | timerStatement
    | action
  )
  ('before' orderDestList)?
  ('after' orderDestList)?
  end
  ('time' timeDestList ';')?
  {





  }
;

orderDestList:
  orderDest (',' orderDest)*
  {  }
;

timeDestList:
  timeDestination (',' timeDestination)*
;

timeDestination:
  (timeDest)? timeInterval
  {

  }
;

timeDest:
  eventName |
  (
    'top' {  }
    | 'bottom' {  }
  )
  (referenceIdentification | labelName)
;

nonOrderableEvent:
  startMethod | endMethod | startSuspension | endSuspension
  | startCoregion | endCoregion | sharedCondition
  | sharedMSCReference | sharedInlineExpr
  | instanceHeadStatement | instanceEndStatement | stop
;

instanceNameList:
  instanceName (',' instanceName)*
  | 'all' {  }
;

multiInstanceEventList:
  multiInstanceEvent (multiInstanceEvent)*
;

multiInstanceEvent:
  condition | mscReference | inlineExpr
;

instanceHeadStatement:
  'instance' (instanceKind)? (decomposition)? end
  {

  }
;

instanceEndStatement:
  'endinstance' end
  {

  }
;

messageEvent:
  messageOutput | messageInput
;

messageOutput:
  'out' msgIdentification 'to' inputAddress
  {

  }
;

messageInput:
  'in' msgIdentification 'from' outputAddress
  {

  }
;

incompleteMessageEvent:
  incompleteMessageOutput | incompleteMessageInput
;

incompleteMessageOutput:
  'out' msgIdentification 'to' 'lost' (inputAddress)?
  {

  }
;

incompleteMessageInput:
  'in' msgIdentification 'from' 'found' (outputAddress)?
  {

  }
;

msgIdentification:
  messageName (',' messageInstanceName)?
  ('(' parameterList ')')?
  {

  }
;

outputAddress:
  (instanceName	| ('env' | referenceIdentification) ('via' gateName)?)
  {

  }
;

referenceIdentification:
  'reference' mscReferenceIdentification
  | 'inline' inlineExprIdentification
;

inputAddress:
  (instanceName
  | ('env' | referenceIdentification) ('via' gateName)?)
  {

  }
;



methodCallEvent:
  callOut | callIn | replyOut | replyIn
;

callOut:
  'call' msgIdentification 'to' inputAddress
  {

  }
;

callIn:
  'receive' msgIdentification 'from' outputAddress
  {

  }
;

replyOut:
  'replyout' msgIdentification 'to' inputAddress
  {

  }
;

replyIn:
  'replyin' msgIdentification 'from' outputAddress
  {

  }
;

incompleteMethodCallEvent:
  incompleteCallOut | incompleteCallIn | incompleteReplyOut | incompleteReplyIn
;

incompleteCallOut:
  'call' msgIdentification 'to' 'lost' (inputAddress)?
  {

  }
;

incompleteCallIn:
  'receive' msgIdentification 'from' 'found' (outputAddress)?
  {

  }
;

incompleteReplyOut:
  'replyout' msgIdentification 'to' 'lost' (inputAddress)?
  {

  }
;

incompleteReplyIn:
  'replyin' msgIdentification 'from' 'found' (outputAddress)?
  {

  }
;

startMethod:
  'method' end
  {

  }
;

endMethod:
  'endmethod' end
  {

  }
;

startSuspension:
  'suspension' end
  {

  }
;

endSuspension:
  'endsuspension' end
  {

  }
;



actualOutGate:
  (gateName)? 'out' msgIdentification 'to' inputDest
  {

  }
;

actualInGate:
  (gateName)? 'in' msgIdentification 'from' outputDest
  {

  }
;

inputDest:
  'lost' ((inputAddress) => inputAddress)? | inputAddress
;

outputDest:
  'found' ((outputAddress) => outputAddress)? | outputAddress
;

defInGate:
  (gateName)? 'out' msgIdentification 'to' inputDest
  {

  }
;

defOutGate:
  (gateName)? 'in' msgIdentification 'from' outputDest
  {

  }
;

actualOrderOutGate:
  gateName 'before' orderDest
  {

  }
;

orderDest:
  eventName | ('env' | referenceIdentification) 'via' gateName
;

actualOrderInGate:
  gateName ('after' orderDest)?
  {

  }
;

defOrderInGate:
  gateName 'before' orderDest
  {

  }
;

defOrderOutGate:
  gateName ('after' orderDestList)?
  {

  }
;

actualCreateOutGate:
  'create' 'out' createGateIdentification 'create' createTarget
  {

  }
;

actualCreateInGate:
  'create' 'in' createGateIdentification
  { //code

  }
;

createTarget:
  instanceName | ('env' | referenceIdentification) ('via' gateName)?
;

defCreateInGate:
  'create' 'out' (createGateIdentification)?
  'create' createTarget
  {

  }
;

defCreateOutGate:
  'create' 'in' createGateIdentification
  {

  }
;

inlineOutGate:
  defOutGate ('external' 'out' msgIdentification 'to' inputDest)?
  {

  }
;

inlineInGate:
  defInGate	('external' 'in' msgIdentification  outputDest)?
  {

  }
;

inlineOutCallGate:
  defOutCallGate ('external' 'call' msgIdentification 'to' inputDest)?
  {

  }
;

inlineInCallGate:
  defInCallGate ('external' 'receive' msgIdentification 'from' outputDest)?
  {

  }
;

inlineOutReplyGate:
  defOutReplyGate ('external' 'replyout' msgIdentification 'to' inputDest)?
  {

  }
;

inlineInReplyGate:
  defInReplyGate ('external' 'replyin' msgIdentification 'from' outputDest)?
  {

  }
;

inlineCreateOutGate:
  defCreateOutGate ('external' create)?
  {

  }
;

inlineCreateInGate:
  defCreateInGate
  ('external' 'create' 'fromt' createSource)?
  {

  }
;

createSource:
  instanceName
  | ('env' | referenceIdentification) ('via' createGateIdentification)?
;

inlineOrderOutGate:
  gateName (('after' orderDestList)? 'external' 'before' orderDest)?
  {

  }
;

inlineOrderInGate:
  gateName 'before' orderDest
  ('external' ('after' orderDestList)?)?
  {

  }
;

actualOutCallGate:
  gateName? 'call' msgIdentification 'to' inputDest
  {

  }
;

actualInCallGate:
  gateName 'receive' msgIdentification 'from' outputDest
  {

  }
;

defInCallGate:
  gateName? 'call' msgIdentification 'tp' inputDest
  {

  }
;

defOutCallGate:
  gateName? 'receive' msgIdentification 'from' outputDest
  {

  }
;

actualOutReplyGate:
  gateName? 'replyout' msgIdentification 'to' inputDest
  {

  }
;

actualInReplyGate:
  gateName? 'replyin' msgIdentification 'from' outputDest
  {

  }
;

defInReplyGate:
  gateName? 'replyout' msgIdentification 'to' inputDest
  {

  }
;

defOutReplyGate:
  gateName? 'replyin' msgIdentification 'from' outputDest
  {

  }
;

/* [Z.120] 1.6.6	-- General ordering defined in 1.6.1
   [Z.120] 1.6.7	-- Condition */

sharedCondition:
  shared? conditionIdentification shared end
  {

  }
;

conditionIdentification:
  'condition' conditionText ;

conditionText:
  (
    conditionNameList {  }
    | 'when'
    (
      conditionNameList {  }
      | '(' expression ')' {  }
    )
    | 'otherwise' {  }
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
  {

  }
;



timerStatement:
  starttimer | stoptimer | timeout
;

starttimer:
  'starttimer' timerName (',' timerInstanceName)? (duration)? ('(' parameterList ')')?
  {

  }
;

duration:
  '[' (minDurationlimit)? (',' maxDurationlimit)? ']'
  {

  }
;

durationlimit:
  (expressionString | 'inf')
  {

  }
;

stoptimer:
  'stoptimer' timerName (',' timerInstanceName)?
  {

  }
;

timeout:
  'timeout' timerName (',' timerInstanceName)?
  ('(' parameterList ')')?
  {

  }
;



action:
  'action' actionStatement
  {

  }
;

actionStatement:
  (informalAction | dataStatementList)
  {

  }
;

informalAction:
  CharacterString
;



create:
  'create' instanceName ('(' parameterList ')')?
  {

  }
;



stop:
  'stop' end
  {

  }
;

/* [Z.120] 1.7		-- Data Concepts
   [Z.120] 1.7.1	-- Introduction
   [Z.120] 1.7.2	-- Syntax interface to external data languages */

parenthesisDeclaration:
  'parenthesis' parDeclList end
  {

  }
;

parDeclList:
  (nestableParPair | nonNestableParPair | equalParDecl | escapeDecl)
  (parDeclList)?
;

nestableParPair:
  'nestable' pairParList end
  {

  }
;

nonNestableParPair:
  'nonnestable' pairParList end
  {

  }
;


equalParDecl:
  'equalpar' equalParList end
  {

  }
;

escapeDecl:
  'escape' escapechar
  {

  }
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






par:
  Name | National | Special | Misc
;







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
  {

  }
;

messageNameList:
  messageName (',' messageNameList)?
;

timerDeclList:
  timerDecl end (timerDeclList)?
;

timerDecl:
  timerNameList (duration)? (':' '(' typeRefList ')')?
  {

  }
;

timerNameList:
  timerName (',' timerName)*
;

typeRefList:
  typeRefString (',' typeRefString)*
;

dynamicDeclList:
  'variables' variableDeclList end
  {

  }
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
  {

  }
;

wildcardDecl:
  'wildcards' variableDeclList
;



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
  (variableString) => variableString
  | wildcard
;

wildcard:
  wildcardString
;



parameterList:
  parameterDefn (',' parameterDefn)*
  {

  }
;

parameterDefn:
  binding | (expression) => expression | pattern
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
  {

  }
;

/* [Z.120] 1.8.7	-- Time Points, Measurements, and Intervals
   [Z.120] 1.8.8	-- Time Points */

timePoint:
  ('@')? timeExpression
  {

  }
;



measurement:
  relMeasurement
  | absMeasurement
;

relMeasurement:
  '&' timePattern
  {

  }
;

absMeasurement:
  '@' timePattern
  {

  }
;



timeInterval:
  ((intervalLabel)? singularTime) => (intervalLabel)? singularTime
  | (intervalLabel)? boundedTime
  (measurement)?
;

intervalLabel:
  'int_boundary' intervalName
;

singularTime:
  '[' timePoint ']'
  {

  }
  | measurement
;

boundedTime:
  '@'?
  ('(' {  })
  (timePoint  {  })?
  ','
  (timePoint  {  })?
  (')' {  } )
  {

  }
;

/* [Z.120] 1.9		-- Structural Concepts
   [Z.120] 1.9.1	-- Coregion */

startCoregion:
  'concurrent' end
  {

  }
;

endCoregion:
  'endconcurrent' end
  {

  }
;



sharedInlineExpr:
  (extraGlobal)? (sharedLoopExpr | sharedOptExpr | sharedAltExpr | sharedSeqExpr
  | sharedParExpr | sharedExcExpr)
  (
    'time' timeInterval end
    {

    }
  )?
  (
    'top' timeDestList end
    {

    }
  )?
  (
    'bottom' timeDestList end
    {

    }
  )?
  {

  }
;

extraGlobal:
  'external';

sharedLoopExpr:
  'loop' (loopBoundary)? 'begin' (inlineExprIdentification)? shared end
  (inlineGateInterface)?
  (
    instanceEventList
    {

    }
  )?
  'loop' 'end' end
  {

  }
;

sharedOptExpr:
  'opt' 'begin' (inlineExprIdentification)? shared end
  (inlineGateInterface)?
  (
    instanceEventList
    {

    }
  )?
  'opt' 'end' end
  {

  }
;

sharedExcExpr:
  'exc' 'begin' (inlineExprIdentification)? shared end
  (inlineGateInterface)?
  (
    instanceEventList
    {

    }
  )?
  'exc' 'end' end
  {

  }
;

sharedAltExpr:
  'alt' 'begin' (inlineExprIdentification)? shared end
  (inlineGateInterface)?
  (
    instanceEventList
    {

    }
  )?
  (
    'alt' end (inlineGateInterface)?
	(
      instanceEventList
      {

      }
    )?
  )*
  'alt' 'end' end
  {

  }
;

sharedSeqExpr:
  'seq' 'begin' (inlineExprIdentification)? shared end
  (inlineGateInterface)?
  (
    instanceEventList
    {

    }
  )?
  (
    'seq' end (inlineGateInterface)?
    (
      instanceEventList
      {

      }
    )?
  )*
  'seq' 'end' end
  {

  }
;

sharedParExpr:
  'par' 'begin' (inlineExprIdentification)? shared end
  (inlineGateInterface)?
  (
    instanceEventList
    {

    }
  )?
  (
    'par' end (inlineGateInterface)?
    (
      instanceEventList
      {

      }
    )?
  )*
  'par' 'end' end
  {

  }
;

inlineExpr:
  (extraGlobal)? (loopExpr | optExpr | altExpr | seqExpr | parExpr | excExpr)
  ('time' timeInterval end {  })?
  ('top' timeDestList end { })?
  ('bottom' timeDestList end {})?
  {

  }
;

loopExpr:
  'loop' (loopBoundary)? 'begin'
  (inlineExprIdentification)? end
  (inlineGateInterface)? mscBody
  'loop' 'end' end
  {

  }
;

optExpr:
  'opt' 'begin' (inlineExprIdentification)? end
  (inlineGateInterface)? mscBody
  'opt' 'end' end
  {

  }
;

excExpr:
  'exc' 'begin' (inlineExprIdentification)? end
  (inlineGateInterface)? mscBody
  'exc' 'end' end
  {

  }
;


altExpr:
  'alt' 'begin' (inlineExprIdentification)? end
  (inlineGateInterface)? mscBody
  ('alt' end (inlineGateInterface)? mscBody)*
  'alt' 'end' end
  {

  }
;

seqExpr:
  'seq' 'begin' (inlineExprIdentification)? end
  (inlineGateInterface)? mscBody
  ('seq' end (inlineGateInterface)? mscBody)*
  'seq' 'end' end
  {

  }
;

parExpr:
  'par' 'begin' (inlineExprIdentification)? end
  (inlineGateInterface)? mscBody
  ('par' end (inlineGateInterface)? mscBody)*
  'par' 'end' end
  {

  }
;

loopBoundary:
  '<' infNatural (',' infNatural)? '>'
  {

  }
;

infNatural:
  'inf' | expression
;

inlineExprIdentification:
  inlineExprName
;

inlineGateInterface:
  ('gate' inlineGate end)+
  {

  }
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



sharedMSCReference:
  'reference' (mscReferenceIdentification ':')?
  mscRefExpr shared end
  ('time' timeInterval end {  })?
  ('top' timeDestList end {})?
  ('bottom' timeDestList end {})?
  referenceGateInterface
  {

  }
;

mscReference:
  'reference' (mscReferenceIdentification ':')?
  mscRefExpr end
  ('time' timeInterval end {  })?
  ('top' timeDestList end {  })?
  ('bottom' timeDestList end {  })?
  referenceGateInterface
  {

  }
;

mscReferenceIdentification:
  mscReferenceName
;

mscRefExpr:
  mscRefParExpr ('alt' mscRefParExpr)*
  {

  }
;

mscRefParExpr:
  mscRefSeqExpr ('par' mscRefSeqExpr)*
  {

  }
;

mscRefSeqExpr:
  mscRefIdentExpr ('seq' mscRefIdentExpr)*
  {

  }
;

mscRefIdentExpr:
  'loop' (loopBoundary)? mscRefIdentExpr {  }
  | 'exc' mscRefIdentExpr { }
  | 'opt' mscRefIdentExpr {  }
  | 'empty' {  }
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
  {

  }
;

actualInstanceParmList:
  actualInstanceParameter (',' actualInstanceParameter)*
;

actualInstanceParameter:
  instanceName
;

actualMessageParameters:
  'msg' actualMessageList
  {

  }
;

actualMessageList:
  messageName ((';' messageName) => ';' messageName)*
;

actualTimerParameters:
  'timer' actualTimerList
  {

  }
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



decomposition:
  'decomposed' (substructureReference)?
  {

  }
;

substructureReference:
  'as' messageSequenceChartName
;



hmsc returns [msc::Msc* n = 0]:
  'expr' mscExpression
  {
    // FIXME
  }
;

mscExpression:
  start (nodeExpression | textDefinition)*
  {

  }
;

start:
  labelNameList end
;

nodeExpression:
  labelName ':' (((timeableNode | node) 'seq' '(' labelNameList ')') | 'end') end
  {

  }
;

labelNameList:
  labelName ('alt' labelName)*
  {

  }
;

timeableNode:
  ('(' mscRefExpr ')' | parExpression )
  (
    'time' timeInterval end
    {

    }
  )?
  (
    'top' timeDestList end
    {

    }
  )?
  ('bottom' timeDestList end
    {

    }
  )?
  {

  }
;

node:
  conditionIdentification {  }
  | 'connect' {  }
;

parExpression:
  'expr' me1 = mscExpression 'endexpr'
  {
  }
  (
    'par' 'expr' me2 = mscExpression 'endexpr'
    {

    }
  )*
;



mscName:
  Name { }
;

instanceName returns [msc::String* n = 0]:
  Name { $n = new msc::String((char*) $Name.text->chars); }
;

actualInstanceParameterName:
  Name {  }
;

eventName:
  Name {  }
;

messageName:
  Name {  }
;

messageInstanceName:
  Name
;

gateName:
  Name
;

conditionName:
  ( Name | CharacterString ) {  }
;

timerName:
  Name {  }
;

timerInstanceName:
  Name {  }
;

intervalName:
  Name  {  }
;

inlineExprName:
  Name  {  }
;

mscReferenceName:
  Name {  }
;

messageSequenceChartName:
  Name {  }
;

labelName:
  Name {  }
;

dataLanguageName:
  Name {  }
;

kindName:
  Name {  }
;



sdlDocumentIdentifier:
  identifier
;

variableIdentifier:
  identifier
;



timeExpression:
  expression
;



timePattern:
  pattern
;



minDurationlimit:
  durationlimit
;

maxDurationlimit:
  durationlimit
;



/* The Z.120 <_expression_ string> non-terminals
   are named expressionString */


expressionString
	: (CharacterString | Name)
		{  }
	;

typeRefString
	: (CharacterString | Name)
		{  }
    ;

variableString
	: (CharacterString | Name)
		{  }
    ;

dataDefinitionString:
  (CharacterString | Name)
		{  }
    ;

wildcardString:
  (CharacterString | Name)
;

createGateIdentification:
  msgIdentification
;
