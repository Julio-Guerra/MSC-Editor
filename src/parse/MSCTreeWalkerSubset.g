/*$Id: MSCTreeWalkerSubset.g,v 1.3 2002/05/03 13:14:16 neukirchen Exp $

  MSC2000-TreeWalker Z.120 rev. 1 (11/2001)

  (Traverses a very basic subset of the AST constructed by MSC2000-Parser

  This file is intended to be used with ANTLR 2.7.1 or higher. ANTLR
  is a parser generator that is based on 'linear approximate'
  lookahead analysis (a kind of weak LL(k) analysis). ANTLR is free
  software provided by jGuru.com (MageLang Institute). For further
  information please refer to http://www.antlr.org.

  For the latest release of all MSC2000 grammar files please have a look at
http://www.itm.mu-luebeck.de/research/main_projects/projects/single_projects/index.php?lang=en&pj_nr=8
  We also invite you to visit the WWW pages of the Institute for Telematics
  at http://www.itm.mu-luebeck.de.

  Copyright (C) 2002 Institute for Telematics
  Medical University of Luebeck
  Ratzeburger Allee 160
  23538 Luebeck
  Germany

  Florian Moesch <fmoesch@itm.mu-luebeck.de> 2000
  Michael Ebner <ebner@itm.mu-luebeck.de> 2001, 2002
  Helmut Neukirchen <neukirchen@itm.mu-luebeck.de> 2001, 2002

  Many thanks to Michael Schmitt for compiler construction consultancy

  Part of this work is supported by the European Commission
  contract IST-11557 INTERVAL.

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License as
  published by the Free Software Foundation; either version 2 of the
  License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
  02111-1307, USA.
*/

options {
//	language  = "Cpp";

}

// ----------------------------------------------------------------------------
//                                 TreeParser
// ----------------------------------------------------------------------------


class MSCTreeWalkerSubset extends TreeParser;


// ----------------------------------------------------------------------------
//                                   Options
// ----------------------------------------------------------------------------


options {
	importVocab = MSCParser;
//    exportVocab = MSCTreeWalker;
	buildAST = false; // necessary? no
    namespaceStd = "std";
    namespaceAntlr = "antlr";

//    genHashLines = false;
//    defaultErrorHandler = true;
//	codeGenMakeSwitchThreshold = 3;
//	codeGenBitsetTestThreshold = 4;
}


// ----------------------------------------------------------------------------
//                                    Rules
// ----------------------------------------------------------------------------


mscTextualFile 
    :  
        #( MscTextualFile 
            (  textualMSCDocument )? // because of MSC-96
            ( messageSequenceChart  )*
        ) 
    ;

textualMSCDocument
    :
        #( DocumentHead
            #( InstanceKind k:Name)
        )
    ;

messageSequenceChart
	:
        #( MessageSequenceChart
            mscHead  
            ( 
                ( mscBody )  => 
                mscBody 
            | hmscBody
            )
            //	   end           // not used until now
        )
    ;

mscHead
	:
        #( MscHead
            name:MscName
            //	   end           // not used until now
            //	   ( Containing )*        // not used until now
        )

    ;

mscBody
	:
        #( MscBody
            (  mscStatement
            )*
        )
    ;

mscStatement
	:
        ( td:TextDefinition
        | #( EventDefinition
                instanceNames
                instanceEvents
            )
        )
    ;

instanceNames
    :
        #( InstanceNames 
            (  ( in:InstanceName
                )* 
            | inall:Name 
            )
        )
    ;       

instanceEvents
	:
        #( InstanceEvents
            ( 
                event
            )+  
        )
    ;

event
    :    
        (                   messageInput 
        |                   messageOutput
        |                   instanceHead
        |                   instanceCreation
        |                   instanceEnd
        |                   startTimer
        |                   timeOut
        |                   condition
        |                   action
        |                   inlineExpr
        |                   mscReference
        |                   startCoregion
        |                   endCoregion
        )
    ;

messageInput
    :
        #( MessageInput
            #( Message mimn:MessageName
                ( misin:InstanceName )?
                ( #( ParameterList
                        ( mip:Parameter
                        )*
                    )
                )?
            )
            #( OutputAddress miin:InstanceName )
            ( #( Label EventName ) )?
            ( #( TimeDest ( timeDest )? timeInterval ) )*
        )
    ;

messageOutput
    :
        #( MessageOutput
            #( Message momn:MessageName
                ( mosin:InstanceName )?
                ( #( ParameterList
                        ( mop:Parameter
                        )*
                    )
                )?
            )
            #( InputAddress moin:InstanceName )
            ( #( Label EventName ) )?
            ( #( TimeDest ( timeDest )? timeInterval ) )* // Time constraints
	    )
    ;

timeDest
    :
      EventName // references "label"s of individual events
    | ( Top | Bottom ) (  ReferenceName | InlineExprName | LabelName ) // references first or last event of MSC reference, Inline expr, HMSC node
    ;

timeInterval
    :
        ( IntervalName )? // Only used to control graphical appearance
        ( #( RelTimeMeasurement timePattern)
        | #( AbsTimeMeasurement timePattern )
        | #( SingularTime timePoint )
        | #( BoundedTime ( AbsTimeMark )? ( LeftOpen | LeftClosed ) ( #( LowerBound timePoint ) )? ( #( UpperBound timePoint ) )? ( RightOpen | RightClosed) )
        )
    ;

timePattern
    :
        VariableString | WildcardString
    ;

timePoint
    :
        #( TimePoint ( AbsTimeMark )? ExpressionString )
    ;

instanceHead
    :
        #( InstanceHead
            // todo: kindDenominator
            //	       ( #( InstanceKind ( kindDenominator )? k:Name)
            
            ( #( InstanceKind  k:Name)  
            )?
        )
    ;


instanceCreation
    :
        #( InstanceCreation
            icin:InstanceName
            ( #( ParameterList
                    ( icpn:Parameter
                    )*
                )
            )?
	    )
    ;

instanceEnd:   
        InstanceEnd
    ;

startTimer
    :
        #( StartTimer
            starttn:TimerName
            ( startin:InstanceName )?
            ( startd:DurationName 
                // msc2000 specific -> not supported until now
                //              | ( ( startd:Duration )?
                //                  #( ParameterList    
                //                     ( starttime:Parameter
                //                     )*)? 
                //                 ) 
            )?
	    )
    ;

timeOut
    :
        #( TimeOut
            stoptn:TimerName
            ( InstanceName )?
            //                  #( ParameterList    
            //                     ( Parameter
            //                     )*)? 

	    )
    ;


condition
    :
        #( Condition
            ( SettingConditionNameList
                ( cond:ConditionName
                )*
            )
        )
    ;

action
    :
        #( Action
            ( an:ActionName
            )*
        )
    ;

inlineExpr
    :
        #( InlineExpr // all inline expressions 
            (                   altExpr
            |                   optExpr
            |                   excExpr
            |                   parExpr
            |                   seqExpr
            |                   loopExpr
            )
        ) // end of inline expressions 
    ;

altExpr
    :
        #( AltExpr
            ( InlineExprName )?
            end
            (
                mscBody
            )* 
//            end // leads to ambiguity if mscBody is empty and exactly one end is present. Morever, comments at this place are not allowed wrt. the graphical grammar
        )
    ;


optExpr
    :
        #( OptExpr 
            ( InlineExprName )?
            end
            mscBody
//            end // leads to ambiguity if mscBody is empty and exactly one end is present. Morever, comments at this place are not allowed wrt. the graphical grammar
        )
    ;

excExpr
    :
        #( ExcExpr 
            ( InlineExprName )?
            end
            mscBody
//            end // leads to ambiguity if mscBody is empty and exactly one end is present. Morever, comments at this place are not allowed wrt. the graphical grammar
        )
    ;

parExpr
    :
        #( ParExpr 
            ( InlineExprName )?
            end
            (
                mscBody
            )*
//            end // leads to ambiguity if mscBody is empty and exactly one end is present. Morever, comments at this place are not allowed wrt. the graphical grammar
        )
    ;

seqExpr
    :
        #( SeqExpr 
            ( InlineExprName )?
            end
            (
                mscBody
            )*
//            end // leads to ambiguity if mscBody is empty and exactly one end is present. Morever, comments at this place are not allowed wrt. the graphical grammar
        )
    ;


loopExpr
    :
        #( LoopExpr 
            ( #( LoopBoundary ( 
                        ( ln:ExpressionString | li:INF ) ( un:ExpressionString | ui:INF )? )? ) )?
            ( InlineExprName )?
            end
  	        mscBody
//            end // leads to ambiguity if mscBody is empty and exactly one end is present. Morever, comments at this place are not allowed wrt. the graphical grammar
        )
    ;

mscReference
    :
        #( MscReference
            ( ReferenceName )?
            #( MscRefExpr 

                #( MscRefParExpr 

                    #( MscRefSeqExpr 

                        ( mn:MscName 
                        )+
                    ) 
                ) 
            ) 
        )
    ;

startCoregion
    :
        ( StartCoregion // Helmut: #( StartCoregion? // Shouldn't make any difference, since this node is a leave
        )
    ;

endCoregion
    :
        ( EndCoregion // Helmut: #( EndCoregion? // Shouldn't make any difference, since this node is a leave
        )
    ;

//
// HMSC
//


hmscBody
	:
        #( HmscBody
            mscExpression
        )
    ;

mscExpression
    :
        #( MscExpression
            ( labelNameList )+ // branch at start symbol if more than one label
            end
            ( nodeExpression
            | td:TextDefinition   // global comment
            )*
        )
    ;

labelNameList 
    :
        #( LabelNameList
            ( ln:LabelName 
            )+
        )
    ;

nodeExpression
    :
        #( NodeExpression 
            ln:LabelName
            ( 
                ( ( timeableNode
                    | node
                    )
                    ( labelNameList )+
                )
            | END
            )
            end
        )
    ;


timeableNode
    :
        #( TimeableNode
            #( MscRefExpr 
                #( MscRefParExpr
                    #( MscRefSeqExpr 
                        (
                            #( Loop          
                                ( #( LoopBoundary ( 
                                            ( ln:ExpressionString | li:INF ) ( un:ExpressionString |
                                                ui:INF )? )? ) )?
                                lmn:MscName 
                            )
                        |  #( Exc emn:MscName )

                            
                        |  #( Opt omn:MscName
                            )
                            //              |  #( Empty )
                            
                        | mn:MscName // ( actualParameter )?
                            // todo: kann mscrefexpr mehr als einmal auftauchen? , in parser ja
                            //parExpression is not supported!!!
                            //     | parExpression  [ hmscHelper ]

                        )+
                    )

                )


            )
            // kann mscrefexpr mehr als einmal auftauchen? in parser ja
            // timer interval fehlt

            
        )
    ;

node
    :
        #( Node
            (
                conditionIdentification    
            | CONNECT 
            )
        )
    ;


parExpression
    :
        #( ParExpression
            ( mscExpression )+
        )
    ;

conditionIdentification
    :
        // AST node since MSCParser 1.55
        ( SettingConditionNameList ( ConditionName )+ // MSC96 conditions considered as SettingConditions in MSC2000
        | GuardingConditionNameList ( Otherwise | ( ConditionName )+ )
        | GuardingConditionExpression ExpressionString
        )

        // AST node until MSCParser 1.54
        //   ( 
        //     ( ConditionName )+
        //   | WHEN ( ( ConditionName )+ | ExpressionString )
        //   | OTHERWISE
        //   )
    ;


end
    :
        ( Comment )?
    ;

