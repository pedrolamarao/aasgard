package aasgard.gdb;

import java.util.BitSet;
import java.util.concurrent.atomic.AtomicBoolean;

import org.antlr.v4.runtime.ANTLRErrorListener;
import org.antlr.v4.runtime.Parser;
import org.antlr.v4.runtime.RecognitionException;
import org.antlr.v4.runtime.Recognizer;
import org.antlr.v4.runtime.atn.ATNConfigSet;
import org.antlr.v4.runtime.dfa.DFA;

final class ErrorListener implements ANTLRErrorListener 
{
	public AtomicBoolean flag = new AtomicBoolean(false);
	
	public void clear ()
	{
		flag.set(false);
	}
	
	public boolean get ()
	{
		return flag.get();
	}

	public void syntaxError (Recognizer<?, ?> recognizer, Object offendingSymbol, int line, int charPositionInLine, String msg, RecognitionException e) 
	{
		flag.set(true);
	}

	public void reportAmbiguity (Parser recognizer, DFA dfa, int startIndex, int stopIndex, boolean exact, BitSet ambigAlts, ATNConfigSet configs)
	{
		flag.set(true);
	}

	public void reportAttemptingFullContext (Parser recognizer, DFA dfa, int startIndex, int stopIndex, BitSet conflictingAlts, ATNConfigSet configs) 
	{
		flag.set(true);
	}

	public void reportContextSensitivity (Parser recognizer, DFA dfa, int startIndex, int stopIndex, int prediction, ATNConfigSet configs)
	{
		flag.set(true);
	}
}