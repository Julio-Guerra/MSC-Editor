// Grammar following MSC Z.120 I-UIT specifications

grammar Msc;

options
{
  language = C;
  k = 2;
}

@parser::includes
{
  # include <vector>

  # include "msc/types.hh"
  # include "msc/all.hh"
  # include "msc/factory.hh"

  # define MAKE(Node, ...)                                   \
      msc::Factory::instance().make_ ## Node(__VA_ARGS__)

  # if defined __GNUC__
  #  pragma GCC system_header
  # elif defined __SUNPRO_CC
  #  pragma disable_warn
  # elif defined _MSC_VER
  #  pragma warning(push, 1)
  # endif
}

@members
{
// Thank you ANTLR for not providing C++ target and make my code unsafe.
extern bool __msc96;
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

fragment
Letter:
 ('a'..'z') | ('A'..'Z')
;

fragment
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
  (Apostrophe
  ((Alphanumeric
  | OtherCharacter
  | Special
  | FullStop
  | Underline
  | Space
  | Apostrophe Apostrophe
  )*)
  Apostrophe)
  {
    pANTLR3_STRING quoted = GETTEXT();
    SETTEXT(quoted->subString(quoted, 1, quoted->len-1));
  }
;

fragment
Apostrophe:
  '\''
;

fragment
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

/* Parser */

// TODO : since the AST is not finished, we check returned
// nodes are not null before adding them to lists, etc. This can be
// deleted once the AST is done.


/* Root rule called by the parser. */
parse returns [msc::Ast* n = 0]:
  r = mscTextualFile { $n = $r.n; }
;

/*
 * Rule used by the parser to start parsing to determine which standard is
 * used by the file.
 * We can determine it with the documentHead rule.
 */
is_msc96 returns [bool result]:
  'msc' .* { return true; }
  | 'mscdocument' .* ('related' 'to' .*)?
  (
    /* The following rules are MSC 2000, containingClause is mandatory */
    (inheritance? ';'
    parenthesisDeclaration?
    dataDefinition
    usingClause
    containingClause) => inheritance? ';'
    parenthesisDeclaration?
    dataDefinition
    usingClause
    containingClause
    /* This rule cannot be empty, if passed, this is MSC 2000 */
    { return false; }
    | ';' { return true; }
  ) .*
;

mscTextualFile returns [msc::Ast* n = 0]
@init { std::vector<msc::MessageSequenceChart*> mscs; }:
  { __msc96 }? ('mscdocument' instanceKind textualMSCDocument
                messageSequenceChart ('endmscdocument' ';')?)
  {
    $n = MAKE(Document,
              MAKE(DocumentHead,
                   $instanceKind.kindDenominator,
                   $instanceKind.identifier),
              // TODO : textualMSCDocument.n,
              $messageSequenceChart.n);
  }
  | { __msc96 }? (msc = messageSequenceChart { mscs.push_back($msc.n); })+
    {
      $n = MAKE(Document, mscs);
    }
  | { !__msc96 }? ('mscdocument' instanceKind ('related' 'to' sdlReference)?
                    textualMSCDocument messageSequenceChart*)+
;

textualMSCDocument:
  { __msc96 }? documentHead textualDefiningPart ((textualUtilityPart) => textualUtilityPart)?
  |  { !__msc96 }? documentHead textualDefiningPart textualUtilityPart
;

documentHead:
  ('related' 'to' sdlReference)?
  (
    { __msc96 }? ';'
    | inheritance? ';'
      parenthesisDeclaration?
      dataDefinition
      usingClause
      containingClause
      messageDeclClause
      timerDeclClause
  )
;

/* [Z.120] 1.4.1	-- Lexical Rules
   [Z.120] 1.4.2	-- Visibility and Naming Rules
   [Z.120] 1.4.3	-- Comment */

end:
  (comment)? ';'
;

comment:
  'comment' CharacterString
;

textDefinition:
  'text' CharacterString end
;

/* [Z.120] 1.4.4	-- Drawing Rules
   [Z.120] 1.4.5	-- Paging of MSCs
   [Z.120] 1.5		-- Message Sequence Chart document */

textualDefiningPart:
  (definingMscReference)*
;

textualUtilityPart:
  ('utilities' (containingClause)? (definingMscReference)*)?
;

definingMscReference:
  'reference' (virtuality)? mscName
;

virtuality returns [msc::MessageSequenceChart::virtuality_enum n]:
  'virtual'     { $n = msc::MessageSequenceChart::VIRTUAL;   }
  | 'redefined' { $n = msc::MessageSequenceChart::REDEFINED; }
  | 'finalized' { $n = msc::MessageSequenceChart::FINALIZED; }
;

usingClause:
  ('using' instanceKind ';')*
;

containingClause:
  (
    ('inst' instanceItem) => 'inst' instanceItem
  )+
;

instanceItem:
  instanceName (':' instanceKind)? (inheritance)?
  (decomposition)?
  (dynamicDeclList | ';')
;

inheritance:
  'inherits' instanceKind
;

messageDeclClause:
  ('msg' messageDecl ';')*
;

timerDeclClause:
  ('timer' timerDecl ';')*
;

sdlReference:
  sdlDocumentIdentifier
;

identifier returns [msc::Identifier* n = 0]:
  qlf = Qualifier? Name
  {
    msc::String* q = $qlf ?
                        new msc::String((char*) $qlf.text->chars)
                        : 0;
    $n = MAKE(Identifier, q, new msc::String((char*) $Name.text->chars));
  }
;

/* [Z.120] 1.6		-- Basic MSC
   [Z.120] 1.6.1	-- Message Sequence Chart */

messageSequenceChart returns [msc::MessageSequenceChart* n = 0]:
  (v = virtuality? 'msc' mscHead (msc = bmsc | msc = hmsc) 'endmsc' end)
  {
    $n = MAKE(MessageSequenceChart,
              *$mscHead.name,
              $v.text ?
              $v.n :
              msc::MessageSequenceChart::UNKNOWN,
              $msc.n);
  }
;

bmsc returns [msc::Msc* n = 0]:
  mscBody
  { // code
    $n = new msc::BasicMsc($mscBody.n);
  } // !code
;

mscHead returns [msc::String* name = 0]:
  n = mscName mscParameterDecl? timeOffset? end
  mscInstInterface? mscGateInterface
  {
    $name = $n.n;
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
;

messageParmDeclList:
  messageDeclList
;

timerParameterDecl:
  'timer' timerParmDeclList
;

timerParmDeclList:
  timerDeclList
;

mscInstInterface:
  containingClause
;

mscGateInterface:
  (mscGateDef)*
;

mscGateDef:
  'gate'
  (
    (gateName? ('in' | 'out')) => mscGate
    | ((gateName)? ('call' | 'receive')) => methodCallGate
    | replyGate
    | createGate
    | orderGate
  ) end
;

mscGate:
  (gateName? 'out') => defInGate | (gateName? 'in') => defOutGate
;

methodCallGate:
  (gateName? 'receive') => defOutCallGate | (gateName? 'call') => defInCallGate
;

replyGate:
  (gateName? 'replyin') => defOutReplyGate
  | (gateName? 'replyout') => defInReplyGate
;

createGate:
  defCreateInGate | defCreateOutGate
;

orderGate:
  defOrderInGate | defOrderOutGate
;

mscBody returns [std::vector<msc::Statement*> n]:
  (
    mscStatement { if ($mscStatement.n) $n.push_back($mscStatement.n); }
  )*
;

mscStatement returns [msc::Statement* n = 0]:
  { __msc96 }? e = msc92EventDefinition { $n = $e.n; }
  | textDefinition
  | e = eventDefinition { $n = $e.n; }
;

msc92EventDefinition returns [ msc::Instance* n = 0; ]:
  'instance' in = instanceName ieh = msc92InstanceHeadStatement iel = instanceEventList
  {
    $n = MAKE(Instance, *$in.n, $ieh.n, $iel.n);
  }
;

msc92InstanceHeadStatement returns [msc::InstanceHead* n = 0]:
  i = (':'? instanceKind)? decomposition? end
  {
    msc::String* kind = $i ? $instanceKind.kindDenominator : 0;
    msc::Identifier* identifier = $i ? $instanceKind.identifier : 0;

    $n = new msc::InstanceHead(kind,
                               identifier,
                               $decomposition.n);
  }
;

eventDefinition returns [msc::Instance* n = 0]:
  (instanceName ':' instanceHeadStatement instanceEventList) => in = instanceName ':' ieh = instanceHeadStatement iel = instanceEventList
  {
    $n = MAKE(Instance, *$in.n, $ieh.n, $iel.n);
  }
  | instanceNameList ':' multiInstanceEventList
;

instanceEventList returns [std::vector<msc::Event*> n]:
  (
    head = instanceEvent
    {
      if ($head.n)
        $n.push_back($head.n);
    }
  )
  (
    (instanceEvent) => tail = instanceEvent
    {
      if ($tail.n)
        $n.push_back($tail.n);
    }
  )*
;

instanceEvent returns [msc::Event* n = 0]:
  (e = orderableEvent | e = nonOrderableEvent)
  {
    $n = $e.n;
  }
;

orderableEvent returns [msc::Event* n = 0]:
  (({ __msc96 }? | 'label') eventName ({ __msc96 }? | end))?
  (
    (messageEvent) => messageEvent { $n = $messageEvent.n; }
    | incompleteMessageEvent
    | (methodCallEvent) => methodCallEvent
    | incompleteMethodCallEvent
    | create
    | timerStatement
    | action
  )
  ('before' orderDestList)?
  ('after' orderDestList)?
  end
  ('time' timeDestList ';')?
;

orderDestList:
  orderDest (',' orderDest)*
;

timeDestList:
  timeDestination (',' timeDestination)*
;

timeDestination:
  (timeDest)? timeInterval
;

timeDest:
  eventName |
  (
    'top'
    | 'bottom'
  )
  (referenceIdentification | labelName)
;

nonOrderableEvent returns [msc::Event* n = 0]:
  startMethod
  | endMethod
  | startSuspension
  | endSuspension
  | startCoregion
  | endCoregion
  | sharedCondition
  | sharedMSCReference
  | sharedInlineExpr
  | instanceEndStatement
  | stop
;

instanceNameList:
  instanceName (',' instanceName)*
  | 'all'
;

multiInstanceEventList:
  multiInstanceEvent (multiInstanceEvent)*
;

multiInstanceEvent:
  condition | mscReference | inlineExpr
;

instanceHeadStatement returns [msc::InstanceHead* n = 0]:
  'instance' instanceKind? decomposition? end
  {
    msc::String* kind = $instanceKind.text ? $instanceKind.kindDenominator : 0;
    msc::Identifier* identifier = $instanceKind.text ?
                                    $instanceKind.identifier : 0;

    $n = new msc::InstanceHead(kind,
                               identifier,
                               $decomposition.n);
  }
;

instanceKind returns [msc::String* kindDenominator = 0,
                      msc::Identifier* identifier = 0]:
  ((kindDenominator identifier) => k = kindDenominator)? id = identifier
  {
    $kindDenominator = $k.n;
    $identifier = $id.n;
  }
;

kindDenominator returns [msc::String* n = 0]:
  kindName { $n = $kindName.n; }
;

decomposition returns [msc::String* n = 0]:
  'decomposed' (substructureReference { $n = $substructureReference.n; })?
;

instanceEndStatement:
  'endinstance' end
;

messageEvent returns [msc::Event* n = 0]:
  m = messageOutput | m = messageInput
  {
    $n = $m.n;
  }
;

messageOutput returns [msc::Message* n = 0]:
  'out' msgIdentification 'to' inputAddress
  {
    // The source is null and will be set when coming back to the instance
    // where this message is defined.
    $n = MAKE(Message, *$msgIdentification.n, 0, $inputAddress.n);
  }
;

messageInput returns [msc::Message* n = 0]:
  'in' msgIdentification 'from' outputAddress
  {
    // The destination is null and will be set when coming back to the instance
    // where this message is defined.
    $n = MAKE(Message, *$msgIdentification.n, $outputAddress.n, 0);
  }
;

incompleteMessageEvent:
  incompleteMessageOutput | incompleteMessageInput
;

incompleteMessageOutput:
  'out' msgIdentification 'to' 'lost' (inputAddress)?
;

incompleteMessageInput:
  'in' msgIdentification 'from' 'found' (outputAddress)?
;

msgIdentification returns [msc::String* n = 0]:
  (messageName (',' messageInstanceName)? ('(' parameterList ')')?)
  {
    $n = $messageName.n;
    // FIXME
  }
;

outputAddress returns [msc::Instance* n = 0]:
  instanceName { $n = MAKE(Instance, *$instanceName.n); }
  | ('env' | referenceIdentification) ('via' gateName)?
;

referenceIdentification:
  'reference' mscReferenceIdentification
  | 'inline' inlineExprIdentification
;

inputAddress returns [msc::Instance* n = 0]:
  (instanceName { $n = MAKE(Instance, *$instanceName.n); }
  | ('env' | referenceIdentification) ('via' gateName)?)
;

methodCallEvent:
  callOut | callIn | replyOut | replyIn
;

callOut:
  'call' msgIdentification 'to' inputAddress
;

callIn:
  'receive' msgIdentification 'from' outputAddress
;

replyOut:
  'replyout' msgIdentification 'to' inputAddress
;

replyIn:
  'replyin' msgIdentification 'from' outputAddress
;

incompleteMethodCallEvent:
  incompleteCallOut | incompleteCallIn | incompleteReplyOut | incompleteReplyIn
;

incompleteCallOut:
  'call' msgIdentification 'to' 'lost' (inputAddress)?
;

incompleteCallIn:
  'receive' msgIdentification 'from' 'found' (outputAddress)?
;

incompleteReplyOut:
  'replyout' msgIdentification 'to' 'lost' (inputAddress)?
;

incompleteReplyIn:
  'replyin' msgIdentification 'from' 'found' (outputAddress)?
;

startMethod:
  'method' end
;

endMethod:
  'endmethod' end
;

startSuspension:
  'suspension' end
;

endSuspension:
  'endsuspension' end
;



actualOutGate:
  (gateName)? 'out' msgIdentification 'to' inputDest
;

actualInGate:
  (gateName)? 'in' msgIdentification 'from' outputDest
;

inputDest:
  'lost' ((inputAddress) => inputAddress)? | inputAddress
;

outputDest:
  'found' ((outputAddress) => outputAddress)? | outputAddress
;

defInGate:
  (gateName)? 'out' msgIdentification 'to' inputDest
;

defOutGate:
  (gateName)? 'in' msgIdentification 'from' outputDest
;

actualOrderOutGate:
  gateName 'before' orderDest
;

orderDest:
  eventName | ('env' | referenceIdentification) 'via' gateName
;

actualOrderInGate:
  gateName ('after' orderDest)?
;

defOrderInGate:
  gateName 'before' orderDest
;

defOrderOutGate:
  gateName ('after' orderDestList)?
;

actualCreateOutGate:
  'create' 'out' createGateIdentification 'create' createTarget
;

actualCreateInGate:
  'create' 'in' createGateIdentification
;

createTarget:
  instanceName | ('env' | referenceIdentification) ('via' gateName)?
;

defCreateInGate:
  'create' 'out' (createGateIdentification)?
  'create' createTarget
;

defCreateOutGate:
  'create' 'in' createGateIdentification
;

inlineOutGate:
  defOutGate ('external' 'out' msgIdentification 'to' inputDest)?
;

inlineInGate:
  defInGate	('external' 'in' msgIdentification  outputDest)?
;

inlineOutCallGate:
  defOutCallGate ('external' 'call' msgIdentification 'to' inputDest)?
;

inlineInCallGate:
  defInCallGate ('external' 'receive' msgIdentification 'from' outputDest)?
;

inlineOutReplyGate:
  defOutReplyGate ('external' 'replyout' msgIdentification 'to' inputDest)?
;

inlineInReplyGate:
  defInReplyGate ('external' 'replyin' msgIdentification 'from' outputDest)?
;

inlineCreateOutGate:
  defCreateOutGate ('external' create)?
;

inlineCreateInGate:
  defCreateInGate
  ('external' 'create' 'fromt' createSource)?
;

createSource:
  instanceName
  | ('env' | referenceIdentification) ('via' createGateIdentification)?
;

inlineOrderOutGate:
  gateName (('after' orderDestList)? 'external' 'before' orderDest)?
;

inlineOrderInGate:
  gateName 'before' orderDest
  ('external' ('after' orderDestList)?)?
;

actualOutCallGate:
  gateName? 'call' msgIdentification 'to' inputDest
;

actualInCallGate:
  gateName 'receive' msgIdentification 'from' outputDest
;

defInCallGate:
  gateName? 'call' msgIdentification 'tp' inputDest
;

defOutCallGate:
  gateName? 'receive' msgIdentification 'from' outputDest
;

actualOutReplyGate:
  gateName? 'replyout' msgIdentification 'to' inputDest
;

actualInReplyGate:
  gateName? 'replyin' msgIdentification 'from' outputDest
;

defInReplyGate:
  gateName? 'replyout' msgIdentification 'to' inputDest
;

defOutReplyGate:
  gateName? 'replyin' msgIdentification 'from' outputDest
;

/* [Z.120] 1.6.6	-- General ordering defined in 1.6.1
   [Z.120] 1.6.7	-- Condition */

sharedCondition:
  shared? conditionIdentification shared end
;

conditionIdentification:
  'condition' conditionText ;

conditionText:
  (
    conditionNameList
    | 'when'
    (
      conditionNameList
      | '(' expression ')'
    )
    | 'otherwise'
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
;

/* [Z.120] 1.6.8	-- Timer */
timerStatement:
  { __msc96 }? (msc96set | msc96reset)
  | starttimer | stoptimer | timeout
;

/* only in MSC96*/
msc96set:
  { __msc96 }? 'set' timerName (',' timerInstanceName)? ('(' durationName ')')?
;

/* only in MSC96 */
msc96reset:
  { __msc96 }? 'reset' timerName (',' timerInstanceName)?
;

starttimer:
  'starttimer' timerName (',' timerInstanceName)? (duration)? ('(' parameterList ')')?
;

duration:
  '[' (minDurationlimit)? (',' maxDurationlimit)? ']'
;

durationlimit:
  (expressionString | 'inf')
;

stoptimer:
  'stoptimer' timerName (',' timerInstanceName)?
;

timeout:
  'timeout' timerName (',' timerInstanceName)?
  ('(' parameterList ')')?
;

action:
  'action' actionStatement
;

actionStatement:
  (informalAction | dataStatementList)
;

informalAction:
  CharacterString
;

create:
  'create' instanceName ('(' parameterList ')')?
;

stop:
  'stop' end
;

/* [Z.120] 1.7		-- Data Concepts
   [Z.120] 1.7.1	-- Introduction
   [Z.120] 1.7.2	-- Syntax interface to external data languages */

parenthesisDeclaration:
  'parenthesis' parDeclList end
;

parDeclList:
  (nestableParPair | nonNestableParPair | equalParDecl | escapeDecl)
  (parDeclList)?
;

nestableParPair:
  'nestable' pairParList end
;

nonNestableParPair:
  'nonnestable' pairParList end
;


equalParDecl:
  'equalpar' equalParList end
;

escapeDecl:
  'escape' escapechar
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
;

messageNameList:
  messageName (',' messageNameList)?
;

timerDeclList:
  timerDecl end (timerDeclList)?
;

timerDecl:
  timerNameList (duration)? (':' '(' typeRefList ')')?
;

timerNameList:
  timerName (',' timerName)*
;

typeRefList:
  typeRefString (',' typeRefString)*
;

dynamicDeclList:
  'variables' variableDeclList end
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
;

/* [Z.120] 1.8.7	-- Time Points, Measurements, and Intervals
   [Z.120] 1.8.8	-- Time Points */

timePoint:
  '@'? timeExpression
;

measurement:
  relMeasurement
  | absMeasurement
;

relMeasurement:
  '&' timePattern
;

absMeasurement:
  '@' timePattern
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
  | measurement
;

boundedTime:
  '@'?
  ('(' )
  (timePoint)?
  ','
  (timePoint)?
  (')'  )
;

/* [Z.120] 1.9		-- Structural Concepts
   [Z.120] 1.9.1	-- Coregion */

startCoregion:
  'concurrent' end
;

endCoregion:
  'endconcurrent' end
;



sharedInlineExpr:
  (extraGlobal)? (sharedLoopExpr | sharedOptExpr | sharedAltExpr | sharedSeqExpr
  | sharedParExpr | sharedExcExpr)
  (
    'time' timeInterval end
  )?
  (
    'top' timeDestList end
  )?
  (
    'bottom' timeDestList end
  )?
;

extraGlobal:
  'external';

sharedLoopExpr:
  'loop' (loopBoundary)? 'begin' (inlineExprIdentification)? shared end
  (inlineGateInterface)?
  (
    instanceEventList
  )?
  'loop' 'end' end
;

sharedOptExpr:
  'opt' 'begin' (inlineExprIdentification)? shared end
  (inlineGateInterface)?
  (
    instanceEventList
  )?
  'opt' 'end' end
;

sharedExcExpr:
  'exc' 'begin' (inlineExprIdentification)? shared end
  (inlineGateInterface)?
  (
    instanceEventList
  )?
  'exc' 'end' end
;

sharedAltExpr:
  'alt' 'begin' (inlineExprIdentification)? shared end
  (inlineGateInterface)?
  (
    instanceEventList
  )?
  (
    'alt' end (inlineGateInterface)?
	(
      instanceEventList
    )?
  )*
  'alt' 'end' end
;

sharedSeqExpr:
  'seq' 'begin' (inlineExprIdentification)? shared end
  (inlineGateInterface)?
  (
    instanceEventList
  )?
  (
    'seq' end (inlineGateInterface)?
    (
      instanceEventList
    )?
  )*
  'seq' 'end' end
;

sharedParExpr:
  'par' 'begin' (inlineExprIdentification)? shared end
  (inlineGateInterface)?
  (
    instanceEventList
  )?
  (
    'par' end (inlineGateInterface)?
    (
      instanceEventList
    )?
  )*
  'par' 'end' end
;

inlineExpr:
  (extraGlobal)? (loopExpr | optExpr | altExpr | seqExpr | parExpr | excExpr)
  ('time' timeInterval end )?
  ('top' timeDestList end )?
  ('bottom' timeDestList end )?
;

loopExpr:
  'loop' (loopBoundary)? 'begin'
  (inlineExprIdentification)? end
  (inlineGateInterface)? mscBody
  'loop' 'end' end
;

optExpr:
  'opt' 'begin' (inlineExprIdentification)? end
  (inlineGateInterface)? mscBody
  'opt' 'end' end
;

excExpr:
  'exc' 'begin' (inlineExprIdentification)? end
  (inlineGateInterface)? mscBody
  'exc' 'end' end
;


altExpr:
  'alt' 'begin' (inlineExprIdentification)? end
  (inlineGateInterface)? mscBody
  ('alt' end (inlineGateInterface)? mscBody)*
  'alt' 'end' end
;

seqExpr:
  'seq' 'begin' (inlineExprIdentification)? end
  (inlineGateInterface)? mscBody
  ('seq' end (inlineGateInterface)? mscBody)*
  'seq' 'end' end
;

parExpr:
  'par' 'begin' (inlineExprIdentification)? end
  (inlineGateInterface)? mscBody
  ('par' end (inlineGateInterface)? mscBody)*
  'par' 'end' end
;

loopBoundary:
  '<' infNatural (',' infNatural)? '>'
;

infNatural:
  'inf' | expression
;

inlineExprIdentification:
  inlineExprName
;

inlineGateInterface:
  ('gate' inlineGate end)+
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
  ('time' timeInterval end )?
  ('top' timeDestList end )?
  ('bottom' timeDestList end )?
  referenceGateInterface
;

mscReference:
  'reference' (mscReferenceIdentification ':')?
  mscRefExpr end
  ('time' timeInterval end )?
  ('top' timeDestList end )?
  ('bottom' timeDestList end )?
  referenceGateInterface
;

mscReferenceIdentification:
  mscReferenceName
;

mscRefExpr:
  mscRefParExpr ('alt' mscRefParExpr)*
;

mscRefParExpr:
  mscRefSeqExpr ('par' mscRefSeqExpr)*
;

mscRefSeqExpr:
  mscRefIdentExpr ('seq' mscRefIdentExpr)*
;

mscRefIdentExpr:
  'loop' (loopBoundary)? mscRefIdentExpr
  | 'exc' mscRefIdentExpr
  | 'opt' mscRefIdentExpr
  | 'empty'
  | (parent)* mscName  ({ __msc96 }? parameterSubstitution | actualParameters)?
  | '(' mscRefExpr ')'
;

/* only used in msc96 */
parameterSubstitution:
  'subst' substitutionList
;

/* only used in msc96 */
substitutionList:
  substitution (',' substitution)*
;

/* only used in msc96 */
substitution:
  replaceMessageInstanceMsc
;

/* only used in msc96 */
replaceMessageInstanceMsc:
  ('msc' | 'inst' | 'msg')? Name 'by' Name
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
;

actualInstanceParmList:
  actualInstanceParameter (',' actualInstanceParameter)*
;

actualInstanceParameter:
  instanceName
;

actualMessageParameters:
  'msg' actualMessageList
;

actualMessageList:
  messageName ((';' messageName) => ';' messageName)*
;

actualTimerParameters:
  'timer' actualTimerList
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

substructureReference returns [msc::String* n = 0]:
  'as' m = messageSequenceChartName { $n = new msc::String((char*) $m.text->chars); }
;

hmsc returns [msc::Msc* n = 0]:
  'expr' mscExpression
;

mscExpression:
  start (nodeExpression | textDefinition)*
;

start:
  labelNameList end
;

nodeExpression:
  labelName ':' (((timeableNode | node) 'seq' '(' labelNameList ')') | 'end') end
;

labelNameList:
  labelName ('alt' labelName)*
;

timeableNode:
  ('(' mscRefExpr ')' | parExpression )
  (
    'time' timeInterval end
  )?
  (
    'top' timeDestList end
  )?
  ('bottom' timeDestList end
  )?
;

node:
  ({ __msc96 }? ('empty' | mscName))
  | conditionIdentification
  | 'connect'
;

parExpression:
  'expr' me1 = mscExpression 'endexpr'
  (
    'par' 'expr' me2 = mscExpression 'endexpr'
  )*
;

mscName returns [msc::String* n = 0]:
  Name { $n = new msc::String((char*) $Name.text->chars);}
;

instanceName returns [msc::String* n = 0]:
  Name { $n = new msc::String((char*) $Name.text->chars); }
;

actualInstanceParameterName returns [msc::String* n = 0]:
  Name { $n = new msc::String((char*) $Name.text->chars); }
;

eventName returns [msc::String* n = 0]:
  Name { $n = new msc::String((char*) $Name.text->chars); }
;

messageName returns [msc::String* n = 0]:
  Name { $n = new msc::String((char*) $Name.text->chars); }
;

messageInstanceName returns [msc::String* n = 0]:
  Name { $n = new msc::String((char*) $Name.text->chars); }
;

gateName returns [msc::String* n = 0]:
  Name { $n = new msc::String((char*) $Name.text->chars); }
;

conditionName returns [msc::String* n = 0]:
  ( Name | CharacterString )
;

/* for MSC96 backward compat. */
durationName returns [msc::String* n = 0]:
  Name { $n = new msc::String((char*) $Name.text->chars); }
;

timerName returns [msc::String* n = 0]:
  Name { $n = new msc::String((char*) $Name.text->chars); }
;

timerInstanceName returns [msc::String* n = 0]:
  Name { $n = new msc::String((char*) $Name.text->chars); }
;

intervalName returns [msc::String* n = 0]:
  Name  { $n = new msc::String((char*) $Name.text->chars); }
;

inlineExprName returns [msc::String* n = 0]:
  Name  { $n = new msc::String((char*) $Name.text->chars); }
;

mscReferenceName returns [msc::String* n = 0]:
  Name { $n = new msc::String((char*) $Name.text->chars); }
;

messageSequenceChartName returns [msc::String* n = 0]:
  Name { $n = new msc::String((char*) $Name.text->chars); }
;

labelName returns [msc::String* n = 0]:
  Name { $n = new msc::String((char*) $Name.text->chars); }
;

dataLanguageName returns [msc::String* n = 0]:
  Name { $n = new msc::String((char*) $Name.text->chars); }
;

kindName returns [msc::String* n = 0]:
  Name { $n = new msc::String((char*) $Name.text->chars); }
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


/* The Z.120 <_expression_ string> non-terminals are named expressionString */
expressionString:
  CharacterString | Name
;

typeRefString:
  CharacterString | Name
;

variableString:
 CharacterString | Name
;

dataDefinitionString:
 CharacterString | Name
;

wildcardString:
  CharacterString | Name
;

createGateIdentification:
  msgIdentification
;
