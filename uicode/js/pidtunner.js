var pidtunner = (function () {
	var updateButton;
	init = function () {
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

		updateButton = $("#setvalue")

	}
	getupdateButton = function () {
		return updateButton;
	}
	newPID = function () {
		return [$("#amount1").val(), $("#amount2").val(), $("#amount3").val()]
	}
	return {
		updateButton : getupdateButton,
		init : init,
		newPID : newPID
	}
})();
