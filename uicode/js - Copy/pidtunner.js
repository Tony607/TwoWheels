var pidtunner = {
	init : function () {
		$("#elem").progressbar({
			value : 20
		});
		$("#slider-vertical1").slider({
			orientation : "vertical",
			range : "min",
			min : 0,
			max : 100,
			value : 80,
			slide : function (event, ui) {
				$("#amount1").val(ui.value);
			}
		});
		$("#slider-vertical2").slider({
			orientation : "vertical",
			range : "min",
			min : 0,
			max : 100,
			value : 60,
			slide : function (event, ui) {
				$("#amount2").val(ui.value);
			}
		});
		$("#slider-vertical3").slider({
			orientation : "vertical",
			range : "min",
			min : 0,
			max : 100,
			value : 20,
			slide : function (event, ui) {
				$("#amount3").val(ui.value);
			}
		});
		$("#amount1").val($("#slider-vertical1").slider("value"));
		$("#amount2").val($("#slider-vertical2").slider("value"));
		$("#amount3").val($("#slider-vertical3").slider("value"));
		$("#setvalue").click(function () {
			//spinner.spinner( "value", 5 );
			$("#slider-vertical3").slider("value", 30)
			$("#amount3").val($("#slider-vertical3").slider("value"));
			console.log("set value");
		});
	}
}
