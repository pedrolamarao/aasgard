package aasgard.gradle.gdb;

import java.util.List;
import java.util.Optional;
import java.util.concurrent.atomic.AtomicInteger;

import aasgard.gdb.GdbMiBaseListener;
import aasgard.gdb.GdbMiParser;
import aasgard.gdb.GdbMiParser.ConstantContext;
import aasgard.gdb.GdbMiParser.ResultContext;
import aasgard.gdb.GdbMiParser.TupleContext;

public final class GdbMiTestListener extends GdbMiBaseListener
{
	private final String symbol;
	
	private final AtomicInteger value = new AtomicInteger(0xFF);
	
	public GdbMiTestListener (String symbol)
	{
		this.symbol = symbol;
	}
	
	public int getValue ()
	{
		return value.get();
	}
	
	@Override 
	public void exitExecAsyncRecord (GdbMiParser.ExecAsyncRecordContext ctx) 
	{
		// filter : record.class = "stopped"
		var record = ctx.record();
		var classs = record.classs();
		if (! "stopped".contentEquals(classs.getText())) return;
		// find record["reason"]
		var reason = constant(record.result(), "reason");
		if (! reason.isPresent()) return;
		// filter : record["reason"]= "watchpoint-trigger"
		if (! "\"watchpoint-trigger\"".contentEquals(reason.get().getText())) return;
		// find record["wpt"]
		var wpt = tuple(record.result(), "wpt");
		if (! wpt.isPresent()) return;
		// find record["wpt"]["exp"]
		var exp = constant(wpt.get().result(), "exp");
		if (! exp.isPresent()) return;
		// filter : record["wpt"]["exp"]
		var symbol = exp.map(r -> r.getText()).map(s -> s.substring(1, s.length() - 1)).get();
		if (! this.symbol.contentEquals(symbol)) return;
		// find record["value"]
		var value = tuple(record.result(), "value");
		if (! value.isPresent()) return;
		// find record["value"]["new"]
		var _new = constant(value.get().result(), "new");
		if (! _new.isPresent()) return;
		// parse record["value"]["new"]
		var _new_s = _new.map(x -> x.getText()).map(s -> s.substring(3, s.length() - 1)).get();
		try {
			var _new_int = Integer.parseInt(_new_s, 16);
			this.value.set(_new_int);
			synchronized (this) { this.notify(); }
		}
		catch (NumberFormatException e) { }
	}
	
	public static Optional<ConstantContext> constant (List<ResultContext> list, String variable)
	{
		for (var result : list) {
			if (variable.contentEquals(result.variable().getText())) {
				var r = result.value().constant();
				if (r != null) {
					return Optional.of(r);
				}
			}
		}
		
		return Optional.empty();
	}
	
	public static Optional<TupleContext> tuple (List<ResultContext> list, String variable)
	{
		for (var result : list) {
			if (variable.contentEquals(result.variable().getText())) {
				var r = result.value().tuple();
				if (r != null) {
					return Optional.of(r);
				}
			}
		}
		
		return Optional.empty();
	}
}