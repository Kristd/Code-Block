var subject = [];
function show() {
    try {
        subject = eval($("#hdnSubject").val());
        var html = "";
        for (var i = 0; i < subject.length; i++) {
            var item = subject[i];
            html += '<div class="headline" id="html_' + i + '"><input type="checkbox" value="' + i + '" class="fl" style="margin-right:5px" id="ckb_' + i + '" onclick="cbk1Click(this)" />' + item.subjecthtmlcontent + '</div>'
            for (var j = 0; j < item.ListChild.length; j++) {
                var item2 = item.ListChild[j];				
                var className = "first-layer";
                //最后一个的样式不一样
                if (k == item.ListChild.length - 1) {
                    className = "first-layer";
                }
                html += '<div class="quesbox" ><div class="' + className + '" id="divColor_' + item2.Id + '"><dl class="qusObj"><dt><span class="qusType" id="lx_' + i + ',' + j + '">' + getTypeName(item2.题目类型) + '</span><input type="checkbox"';
                if (item2.ListChild.length == 0) {
                    html += 'islast="1" ';
                }

                html += ' value="' + i + ',' + j + '" class="rad" id="ckb_' + i + ',' + j + '" onclick="cbk1Click(this)" /></dt>' +
                '<dd>';
                if (item2.ListChild.length == 0) {
                    html += '<span class="fl"  style="margin-right:5px;color:red" id="spanfz_' + i + ',' + j + '">' + item2.分值 + '分</span>';
                }
                html += '<span class="fl">' + item2.套卷序号 + '. </span><span id="html_' + i + ',' + j + '">' + item2.subjecthtmlcontent.replace(/<check>/g, "<span style='color:blue'>").replace(/<\/check>/g, "</span>").replace(/<nocheck>/g, "<span style='color:red'>").replace(/<\/nocheck>/g, "</span>") + '</span></dd></dl>';
                if (item2.ListChild.length == 0) {
                    html += '<div class="quesopmenu"><a href="javascript:void(0);" onclick="window.external.SubjectSelect(\''+item2.Id+'\',\''+item2.ParentId+'\');">选定</a><a href="javascript:typeBox(\'' + i + ',' + j + '\');" class="detail">修改</a><a class="del" index="' + i + ',' + j + '" onclick="menuDel(this,\'quesbox\')">删除</a></div>';
                }
                html += '</div>';




                for (var k = 0; k < item2.ListChild.length; k++) {
                    var item3 = item2.ListChild[k];		
                    var className = "sec-layer";
                    //最后一个的样式不一样
                    if (k == item2.ListChild.length - 1) {
                        className = "sec-layer";
                    }
                    html += '<div class="' + className + '" id="divColor_' + item3.Id + '"><dl class="qusObj"><dt><span class="qusType" id="lx_' + i + ',' + j + ',' + k + '">' + getTypeName(item3.题目类型) + '</span><input id="ckb_' + i + ',' + j + ',' + k + '" value="' + i + ',' + j + ',' + k + '" islast="1" type="checkbox" class="rad"></dt>' +
                    '<dd><span class="fl"  style="margin-right:5px;color:red" id="spanfz_' + i + ',' + j + ',' + k + '">' + item3.分值 + '分</span><span class="fl">(' + item3.套卷序号 + '). </span><span id="html_' + i + ',' + j + ',' + k + '">' + item3.subjecthtmlcontent.replace(/<check>/g, "<span style='color:blue'>").replace(/<\/check>/g, "</span>").replace(/<nocheck>/g, "<span style='color:red'>").replace(/<\/nocheck>/g, "</span>") + '</span></dd></dl>';
                    html += '<div class="quesopmenu"><a href="javascript:void(0);" onclick="window.external.SubjectSelect(\''+item3.Id+'\',\''+item3.ParentId+'\');">选定</a><a href="javascript:typeBox(\'' + i + ',' + j + ',' + k + '\');" class="detail">修改</a><a class="del" index="' + i + ',' + j + ',' + k + '"  onclick="menuDel(this,\'sec-layer\')">删除</a></div></div>';
                    //不是最后一个
                    if (k < item2.ListChild.length - 1 && !item3.IsHiddenDelete) {
                        var tempi = item2.ListChild[k + 1].套卷序号 - item3.套卷序号;
                        if (tempi != 1) {
                            for (var s = item3.套卷序号 + 1; s < item2.ListChild[k + 1].套卷序号; s++) {
                                html += '<div class="sec-layer sec-green"  title="漏题，请补充此题"><dl class="qusObj"><dt><span class="qusType">单选</span><input type="checkbox"  value="' + i + ',' + j + ',' + s + '"  class="rad"></dt>' +
                                '<dd><span class="fl"  style="margin-right:5px;color:red">1分</span><span class="fl">(' + s + '). </span><span></span></dd></dl>';
                                html += '<div class="quesopmenu"><a href="javascript:typeBox(\'' + i + ',' + j + ',' + k + '\',1,' + s + ',\'' + item3.ParentId + '\');" class="detail">修改</a><a class="del" onclick="menuDel(this,\'sec-layer\',1)">删除</a></div></div>';
                            }
                        }
                    }
                }
                html += "</div>";

                //不是最后一个
                if (j < item.ListChild.length - 1 && !item2.IsHiddenDelete) {
                    var tempi = item.ListChild[j + 1].套卷序号 - item2.套卷序号;
                    if (tempi != 1) {
                        for (var s = item2.套卷序号 + 1; s < item.ListChild[j + 1].套卷序号; s++) {
                            html += '<div class="quesbox" ><div class="first-layer fir-green" title="漏题，请补充此题"><dl class="qusObj"><dt><span class="qusType">单选</span><input type="checkbox" ';
                            html += ' value="' + i + ',' + s + '" class="rad"/></dt><dd><span class="fl"  style="margin-right:5px;color:red">1分</span>';
                            html += '<span class="fl">' + s + '. </span><span></span></dd></dl>';
                            html += '<div class="quesopmenu"><a href="javascript:typeBox(\'' + i + ',' + j + '\',1,' + s + ',\'' + item2.ParentId + '\');" class="detail">修改</a><a class="del" onclick="menuDel(this,\'quesbox\',1)">删除</a></div>';
                            html += '</div></div>';
                        }
                    }
                }
            }
        }
        $(".ccquestGroup").html(html);
        boxType('.sec-layer');
        updateAllFz();
    } catch (e) {
        //alert("您的试卷不符合规则，识别出错!")
    }
}
var barTop = $('.quesSetBar').offset().top;
$(window).scroll(function () {
    var scTop = $(window).scrollTop();
    if (scTop > barTop && scTop != 0) {
        $('.quesSetBar').addClass("questCurr");
    } else if (scTop == 0) {
        $('.quesSetBar').removeClass("questCurr");
    }
});

function menuDel(obj, divClass, type) {
    var obj = $(obj);
    if (type != 1) {
        txtchange(obj.attr("index"), 2);
    }
    obj.closest('.' + divClass).remove();
}

$('.typeTab a').live("click", function (e) {
    var i = $(this).index();
    $(this).addClass("curr").siblings('.typeTab a').removeClass("curr");
    $('.typeBox').eq(i).show().siblings('.typeBox').hide();
});
function boxType(obj) {
    $(obj).each(function () {
        $(this).hover(
            function (e) { $(this).addClass("questSel").find('.quesopmenu').show(); },
            function () { $(this).removeClass("questSel").find('.quesopmenu').hide(); }
        );
    })
    $('.first-layer').hover(
        function () {
            $(this).closest('.quesbox').addClass("questSel");
            $(this).find('.quesopmenu:first').show();
        },
        function () {
            $(this).closest('.quesbox').removeClass("questSel");
            $(this).find('.quesopmenu:first').hide();
        }
    );
}




$('body').click(function () { $('.markTip').hide(); });//点击页面时右键菜单消失

function typeChange(type, index) {
    isUpdateType = true;
    if (type == "1" || type == "8" || type == "2") {
        $(document.getElementById("sltkgt_" + index)).attr("disabled", true).val("1");

    } else {
        $(document.getElementById("sltkgt_" + index)).attr("disabled", false).val("0");
    }
    //$(document.getElementById("sltkgt_"+index)).attr("disabled",isDisabled);	
    //alert($(document.getElementById("sltkgt_"+index)).attr("id"))
}

function getItem(index) {
    var item = {};
    var indexs = index.split(',');
    if (indexs.length == 1) {
        item = subject[indexs[0]];
    } else if (indexs.length == 2) {
        item = subject[indexs[0]].ListChild[indexs[1]];
    } else if (indexs.length == 3) {
        item = subject[indexs[0]].ListChild[indexs[1]].ListChild[indexs[2]];
    }
    return item;
}
var htmlValue = "";
var editors =[];
var editorInstance;
var editorInstance2;
var editorInstance3;
var lx = "";
var fz = "";
var currentIndex = -1;
var isUpdateType;
//属性弹出框
var typeBox = function (index, type, xh, parentId) {
	editors = [];
    if (type != 1) {
        isUpdateType = false;
        var item = getItem(index);			
        var str = '<div class="typeTab"><a href="javascript:;" class="curr">题干</a><a href="javascript:;">答案</a><a href="javascript:;">属性</a><a href="javascript:;">解题思路</a></div>' +
			'<div class="typeBox">' +
					'<textarea id="div1tg" name="div1_' + index + '" style="height:300px;visibility:hidden;">' + item.subjecthtmlcontent + '</textarea>' +
			'</div>';
        str += '<div class="typeBox" id="divss" style="height:250px; overflow:auto; *zoom:1">';
        //单选题
        if (item.题目类型 == 1) {
            for (var k = 0; k < item.answers.length; k++) {
                str += '<input type="radio" value="' + item.answers[k].sort + '" name="rdAnswer" ';
                if (item.answers[k].isanswer) {
                    str += ' checked="checked" ';
                }
                str += '/>' + item.answers[k].content + '<br/>';
            }
        } else if (item.题目类型 == 3) {  //填空题		
            for (var k = 0; k < item.answers.length; k++) {
                str += '<textarea id="rdAnswer_' + item.answers[k].sort + '" name="rdAnswer_' + index + '" sort="' + item.answers[k].sort + '" style="height:50px;visibility:hidden;">' + item.answers[k].content + '</textarea>';               
            }
        } else if (item.题目类型 == 8) {  //判断题
            str += '<input type="radio" value="1" name="rdAnswer" ';
            if (item.answers[0].content == "1") {
                str += ' checked="checked" ';
            }
            str += '/>正确';
            str += '<input type="radio" value="0" name="rdAnswer" ';
            if (item.answers[0].content != "1") {
                str += ' checked="checked" ';
            }
            str += '/>错误';
        } else if (item.题目类型 == 2) { //多选题
            for (var k = 0; k < item.answers.length; k++) {
                str += '<input type="checkbox"  value="' + item.answers[k].sort + '"  name="rdAnswer" ';
                if (item.answers[k].isanswer) {
                    str += ' checked="checked" ';
                }
                str += '/>' + item.answers[k].content + '<br/>';
            }
        } else {
            str += ' <textarea id="txt1da" name="txtda_' + index + '" style="height:300px;visibility:hidden;">' + item.answer.subjecthtmlanswer + '</textarea>';
        }
        str += '</div>'
        str += '<ul class="typeBox" style="display:none;">' +
            '<li><label for="">分值：</label><input type="text" id="txtfz_' + index + '" value="' + item.分值 + '" /></li>' +
            '<li><label for="">题型：</label><select id="slType_' + index + '" onchange="typeChange(this.value,\'' + index + '\')"><option value="1" ' + (item.题目类型 == 1 ? "selected=selected:" : "") + '>单选题</option><option value="3" ' + (item.题目类型 == 3 ? "selected=selected:" : "") + '>填空题</option><option value="6" ' + (item.题目类型 == 6 ? "selected=selected:" : "") + '>简答题</option><option value="8" ' + (item.题目类型 == 8 ? "selected=selected:" : "") + '>判断题</option><option value="2" ' + (item.题目类型 == 2 ? "selected=selected:" : "") + '>多选题</option></select></li>';
        var isDisabled = "";
        if (item.题目类型 == 1 || item.题目类型 == 8 || item.题目类型 == 2) {
            isDisabled = "disabled='isDisabled'";
        }
        str += '<li><label for="">主客观：</label><select class="ddc" id="sltkgt_' + index + '" ' + isDisabled + '>';
        if (item.客观题 == 1) {
            str += '<option value="0">主观题</option><option value="1" selected="selected">客观题</option>';
        } else {
            str += '<option value="0" selected="selected">主观题</option><option value="1">客观题</option>';
        }
        str += '</select></li></ul>';
		str+='<div class="typeBox" id="divjtsls">' +
					'<textarea id="div1jtsl" name="divjtsl_' + index + '" style="height:300px;visibility:hidden;">' + item.questionthinking + '</textarea>' +
			'</div>';
        //dlg.Common("试题修改",str,700,function(){txtchange(index,1);
        //setTimeout(function(){
        //	document.getElementById("html_"+index).innerHTML = 	htmlValue;
        //	document.getElementById("lx_"+index).innerHTML = getTypeName(lx);
        //},100);});
        currentIndex = index;
        dialog('属性窗口', str, 700, 2);       
        editorInstance = KindEditor.create('#div1tg', {
                resizeType: 0,
				filterMode: false,
                allowPreviewEmoticons: false,
                allowImageUpload: false,
                items: [
                    'fontname', 'fontsize', '|', 'forecolor', 'hilitecolor', 'bold', 'italic', 'underline',
                    'removeformat', '|', 'justifyleft', 'justifycenter', 'justifyright', 'insertorderedlist',
                    'insertunorderedlist', '|', 'emoticons', 'image', 'link']
            });						
			for(var i=0;i<item.answers.length;i++){
			    editors.push(KindEditor.create('#rdAnswer_' + item.answers[i].sort, {
					resizeType: 0,
					allowPreviewEmoticons: false,
					filterMode: false,
					allowImageUpload: false,
					items: [
						'fontname', 'fontsize', '|', 'forecolor', 'hilitecolor', 'bold', 'italic', 'underline',
						'removeformat', '|', 'justifyleft', 'justifycenter', 'justifyright', 'insertorderedlist',
						'insertunorderedlist', '|', 'emoticons', 'image', 'link']
				}))
			 }
            if (item.题目类型 == 6) {
                editorInstance2 = KindEditor.create('#txt1da', {
                    resizeType: 0,
                    allowPreviewEmoticons: false,
					filterMode: false,
                    allowImageUpload: false,
                    items: [
                        'fontname', 'fontsize', '|', 'forecolor', 'hilitecolor', 'bold', 'italic', 'underline',
                        'removeformat', '|', 'justifyleft', 'justifycenter', 'justifyright', 'insertorderedlist',
                        'insertunorderedlist', '|', 'emoticons', 'image', 'link']
                });
            }
            editorInstance3 = KindEditor.create('#div1jtsl', {
                    resizeType: 0,
                    allowPreviewEmoticons: false,
					filterMode: false,
                    allowImageUpload: false,
                    items: [
                        'fontname', 'fontsize', '|', 'forecolor', 'hilitecolor', 'bold', 'italic', 'underline',
                        'removeformat', '|', 'justifyleft', 'justifycenter', 'justifyright', 'insertorderedlist',
                        'insertunorderedlist', '|', 'emoticons', 'image', 'link']
                });	
        setTimeout(function () {
            if (editorInstance) {
                editorInstance.focus();
            }
			$(".ke-statusbar").css("display","none");
        }, 500);
        $("#divss").css("display", "none");
		$("#divjtsls").css("display", "none");
        //document.write(str);
    } else {
        var str = '<div class="typeTab"><a href="javascript:;" class="curr">题干</a><a href="javascript:;">答案</a><a href="javascript:;">属性</a></div>' +
        '<div class="typeBox" >' +
                ' <textarea id="div1_s0" name="div1_s0" style="height:300px;visibility:hidden;"></textarea>' +
        '</div>';
        str += '<div class="typeBox" id="div_boxs0" >';
        str += ' <textarea id="txtda_s0" name="txtda_s0" style="height:300px;visibility:hidden;"></textarea>';
        str += '</div>'
        str += '<ul class="typeBox" style="display:none;">' +
        '<li><label for="">分值：</label><input type="text" xh=' + xh + ' parentId="' + parentId + '" id="txtfz_s0" value="1" /></li>' +
        '<li><label for="">题型：</label><select id="slType_s0" onchange="typeChange(this.value,0)"><option value="1">单选题</option><option value="3">填空题</option><option value="6">简答题</option><option value="8">判断题</option><option value="2">多选题</option></select></li>';
        var isDisabled = "disabled='isDisabled'";
        str += '<li><label for="">主客观：</label><select class="ddc" id="sltkgt_s0" ' + isDisabled + '>';
        str += '<option value="0">主观题</option><option value="1" selected="selected">客观题</option>';
        str += '</select></li></ul>';
        currentIndex = "s0";
        dialog('属性窗口', str, 700, 2);      
            editorInstance = KindEditor.create('#div1_s0', {
                resizeType: 0,
                allowPreviewEmoticons: false,
				filterMode: false,
                allowImageUpload: false,
                items: [
                    'fontname', 'fontsize', '|', 'forecolor', 'hilitecolor', 'bold', 'italic', 'underline',
                    'removeformat', '|', 'justifyleft', 'justifycenter', 'justifyright', 'insertorderedlist',
                    'insertunorderedlist', '|', 'emoticons', 'image', 'link']
            });
            editorInstance2 = KindEditor.create('#txtda_s0', {
                resizeType: 0,
                allowPreviewEmoticons: false,
				filterMode: false,
                allowImageUpload: false,
                items: [
                    'fontname', 'fontsize', '|', 'forecolor', 'hilitecolor', 'bold', 'italic', 'underline',
                    'removeformat', '|', 'justifyleft', 'justifycenter', 'justifyright', 'insertorderedlist',
                    'insertunorderedlist', '|', 'emoticons', 'image', 'link']
            });
            $("#div_boxs0").css("display", "none");  
            setTimeout(function () {
                if (editorInstance) {
                    editorInstance.focus();
                }
			$(".ke-statusbar").css("display","none");
        }, 200);
    }
}
function getTypeName(type) {
    if (type == 1) {
        return "单选";
    } else if (type == 2) {
        return "多选";
    } else if (type == 3) {
        return "填空";
    } else if (type == 6) {
        return "简答";
    } else if (type == 8) {
        return "判断";
    } else if (type == 5) {
        return "阅读";
    }
    return "";
}

function check_validate1(value) {
    var reg = new RegExp("^[0-9]*$");
    if (reg.test(value)) {
        return true;
    }
    return false;
}

function txtchange(index, type) {
    var json = [];
    var updateValue = document.getElementById('hdn_update');
    if (updateValue.value != '') {
        json = eval(updateValue.value);
    }
    var item = getItem(index);
    if (index == "s0") {
        item = {};
        item.answers = [];
        item.answer = {};
        item.ListChild = [];
        item.ErrorMsg = "";
        item.Id = "";
        item.Level = 0;
        item.答案 = {};
    }
    if (type == 1) {
        var txtfz = $(document.getElementById("txtfz_" + index));
        var slType = $(document.getElementById("slType_" + index));
        var sltkgt = $(document.getElementById("sltkgt_" + index));
        item.题目类型 = slType.val();
        lx = slType.val();
        item.客观题 = sltkgt.val();		
		htmlValue = editorInstance.html();
		while(htmlValue.indexOf("<span style=\"border-bottom:#000 1px solid;padding-bottom:2px;line-height:24px;padding-left:0px;padding-right:0px;display:inline-block;height:24px;vertical-align:6px;padding-top:0px;\" spanitem=\"1\"><span style=\"border-bottom:#000 1px solid;padding-bottom:2px;line-height:20px;padding-left:5px;padding-right:5px;display:inline-block;height:20px;font-size:12px;padding-top:0px;\" spanitem=\"1\">")!=-1){
			htmlValue = htmlValue.replace("<span style=\"border-bottom:#000 1px solid;padding-bottom:2px;line-height:24px;padding-left:0px;padding-right:0px;display:inline-block;height:24px;vertical-align:6px;padding-top:0px;\" spanitem=\"1\"><span style=\"border-bottom:#000 1px solid;padding-bottom:2px;line-height:20px;padding-left:5px;padding-right:5px;display:inline-block;height:20px;font-size:12px;padding-top:0px;\" spanitem=\"1\">","<span style=\"border-bottom:1px solid #000; padding:0 0 2px; display:inline-block; vertical-align:12px; *vertical-align:6px;height:20px; line-height:20px; _height:24px; _line-height:24px;\" spanitem=\"1\"><span spanitem=\"1\" style=\"border-bottom:1px solid #000; padding:0 5px 2px; display:inline-block; font-size:12px; height:16px; _height:20px; line-height:20px\">");
		}
        item.subjecthtmlcontent = htmlValue;		
        if (item.subjecthtmlcontent == "") {
            alert("题干内容不能为空!");
            return false;
        }
		item.questionthinking = editorInstance3.html();        
        item.分值 = txtfz.val();
        if (!check_validate1(txtfz.val())) {
            alert("分值只能为整数!");
            return false;
        }
        fz = item.分值;
        if (index == "s0") {
            item.State = 1;
            item.Index = "";
            item.Id = txtfz.attr("parentId") + "." + txtfz.attr("xh");
            item.套卷序号 = txtfz.attr("xh");
            item.ParentId = txtfz.attr("parentId");
            item.answer.subjecthtmlanswer = editorInstance2.html();
            item.答案.subjecthtmlanswer = item.answer.subjecthtmlanswer;
        } else {
            document.getElementById("spanfz_" + index).innerHTML = fz + "分";
            updateAllFz();
            //修改题目类型的时候不修改答案
            if (!isUpdateType) {
                var anwerHTMl = "";
                if (item.题目类型 == 1) {
                    var radio = $("input[name='rdAnswer']:checked");
                    var sort = radio.val();
                    anwerHTMl = GetAnswer(sort);
                    for (var k = 0; k < item.answers.length; k++) {
                        if (sort == item.answers[k].sort) {
                            item.answers[k].isanswer = true;
                        } else {
                            item.answers[k].isanswer = false;
                        }
                    }
                } else if (item.题目类型 == 3) {  //填空题
                    for (var k = 0; k < item.answers.length; k++) {					
                        item.answers[k].content = editors[k].html();
                        anwerHTMl += item.answers[k].content + "|";
                    }
                    anwerHTMl = anwerHTMl.substring(0, anwerHTMl.length - 1);
                } else if (item.题目类型 == 8) {  //判断题
                    item.answers[0].content = $("input[name='rdAnswer']:checked").val();
                    anwerHTMl = item.answers[0].content == 1 ? "正确" : "错误"
                } else if (item.题目类型 == 2) { //多选题
                    var radio = $("input[name='rdAnswer']:checked");
                    for (var k = 0; k < item.answers.length; k++) {
                        item.answers[k].isanswer = false;
                        $.each(radio, function (i, rad) {
                            sort = $(rad).val();
                            if (sort == item.answers[k].sort) {
                                item.answers[k].isanswer = true;
                                anwerHTMl += GetAnswer(sort);
                            }
                        });
                    }
                } else {
                    item.answers[0].content = editorInstance2.html();

                    anwerHTMl = item.answers[0].content;
                }
                item.answer.subjecthtmlanswer = anwerHTMl;
                item.答案.subjecthtmlanswer = item.answer.subjecthtmlanswer;
            }
        }
        if (item.answer.subjecthtmlanswe == "") {
            alert("题目答案不能为空!");
            return false;
        }
    } else if (type == 2) {
        item.State = -1;
    }
    item.Index = index;
    json.push(item);
    updateValue.value = $.toJSON(json);
    return true;
}

function GetAnswer(i) {
    if (i == 1) {
        return "A";
    } else if (i == 2) {
        return "B";
    } else if (i == 3) {
        return "C";
    } else if (i == 4) {
        return "D";
    } else if (i == 5) {
        return "E";
    } else if (i == 6) {
        return "F";
    } else if (i == 7) {
        return "G";
    } else if (i == 8) {
        return "H";
    } else if (i == 9) {
        return "I";
    }
}

function updateSubject(json, indexs) {
    subject = eval(json);
    indexs = indexs.split('|');
    $.each(indexs, function (i, index) {

        var item = getItem(index);

        document.getElementById("html_" + index).innerHTML = item.subjecthtmlcontent.replace(/<check>/g, "<span style='color:blue'>").replace(/<\/check>/g, "</span>").replace(/<nocheck>/g, "<span style='color:red'>").replace(/<\/nocheck>/g, "</span>");
        document.getElementById("lx_" + index).innerHTML = getTypeName(item.题目类型);
    });

}

function updateAll() {
    var allCheck = $("input[islast='1']:checked");
    if (allCheck.length == 0) {
        alert("请先选择要批量修改的试题");

    } else {
        typeBoxAll(allCheck);
    }
}

var typeBoxAll = function (allCheck) {
    var item = getItem(allCheck.eq(0).val());
    isUpdateType = true;
    var index = -1;
    var str = '';
    str += '<ul class="typeBox">' +
        '<li><label for="">分值：</label><input type="text" id="txtfz_' + index + '" value="' + item.分值 + '" /></li>' +
        '<li><label for="">题型：</label><select id="slType_' + index + '" onchange="typeChange(this.value,\'' + index + '\')"><option value="1" ' + (item.题目类型 == 1 ? "selected=selected:" : "") + '>单选题</option><option value="3" ' + (item.题目类型 == 3 ? "selected=selected:" : "") + '>填空题</option><option value="6" ' + (item.题目类型 == 6 ? "selected=selected:" : "") + '>简答题</option><option value="8" ' + (item.题目类型 == 8 ? "selected=selected:" : "") + '>判断题</option><option value="2" ' + (item.题目类型 == 2 ? "selected=selected:" : "") + '>多选题</option></select></li>';
    var isDisabled = "";
    if (item.题目类型 == 1 || item.题目类型 == 8 || item.题目类型 == 2) {
        isDisabled = "disabled='isDisabled'";
    }
    str += '<li><label for="">主客观：</label><select class="ddc" id="sltkgt_' + index + '" ' + isDisabled + '>';
    if (item.客观题 == 1) {
        str += '<option value="0">主观题</option><option value="1" selected="selected">客观题</option>';
    } else {
        str += '<option value="0" selected="selected">主观题</option><option value="1">客观题</option>';
    }
    str += '</select></li></ul>';
    dialog('属性窗口', str, 300, 1);
}


function txtchangeAll(type) {
    var allCheck = $("input[islast='1']:checked");
    if (allCheck.length == 0) {
        alert("请先选择要修改的试题,阅读理解题不能批量修改属性");
        return;
    }
    var json = [];
    var updateValue = document.getElementById('hdn_update');
    if (updateValue.value != '') {
        json = eval(updateValue.value);
    }
    var txtfz = $(document.getElementById("txtfz_-1"));
    var slType = $(document.getElementById("slType_-1"));
    var sltkgt = $(document.getElementById("sltkgt_-1"));
    if (!check_validate1(txtfz.val())) {
        alert("分值只能为整数!");
        return false;
    }

    $.each(allCheck, function (i, obj) {
        var index = $(obj).val();
        var item = getItem(index);
        if (type == 1) {
            item.分值 = txtfz.val();
            fz = item.分值;
            item.题目类型 = slType.val();
            lx = slType.val();
            item.客观题 = sltkgt.val();
            item.Index = index;
            document.getElementById("lx_" + index).innerHTML = getTypeName(lx);
            document.getElementById("spanfz_" + index).innerHTML = fz + "分";
        } else if (type == 2) {
            item.State = -1;
        }
        json.push(item);
    });
    updateAllFz();
    updateValue.value = $.toJSON(json);
    $("input[type='checkbox']").removeAttr("checked");
    return true;
}

function updateAllFz() {
    var allFz = 0;
    $.each($("span[id^='spanfz_']"), function (i, item) {
        allFz += parseInt($(item).html().replace("分"));
    });
    $("#span_fz").html(allFz + "分");
}

function cbk1Click(obj) {
    var obj = $(obj);
    if (obj.attr("checked")) {
        $("input[id^='" + obj.attr("id") + ",']").attr("checked", obj.attr("checked"));
    } else {
        $("input[id^='" + obj.attr("id") + ",']").removeAttr("checked");
    }
}

function CheckDivColor(json) {
    json = eval(json);
    var allColor = $(".sec-red,.fir-red,.sec-yellow,.fir-yellow");
    var isClear = true;
    $.each(allColor, function (index, item) {
        $(item).removeClass("sec-yellow").removeClass("fir-yellow").removeClass("sec-red").removeClass("fir-red").attr("title", "");				   
    });
    for (var i = 0; i < json.length; i++) {
        var className = "sec-red";
        var item = json[i];		
        if (item.ColorState == 0) {
            if (item.Level == 2) {
                className = "fir-red";
            }
        } else if (item.ColorState == 1) {
            if (item.Level == 2) {
                className = "fir-yellow";
            } else if (item.Level == 3) {
                className = "sec-yellow";
            }
        }
        $(document.getElementById("divColor_" + item.Id)).addClass(className).attr("title", item.ErrorMsg);
    }
}





function dialog(title, content, diaW, type) {
    var shadow = '<div class="shadow"></div>';
    var dialogHtml = '\
	<div class="dialog">\
		<div class="tNav"><h2>'+ title + '</h2><a href="javascript:;" class="close"></a></div>\
		<div class="dia-con">'+ content + '</div>\
		<div class="dia-btm"><a href="javascript:;" class="btn yes">确定</a><a href="javascript:;" class="btn no">取消</a></div>\
	</div>';
    $(dialogHtml).appendTo('body');
    $(shadow).appendTo('body');
    diaPos('.dialog', '.shadow', diaW);
    $('.shadow,.dialog').show();
    $('.dialog .no,.dialog .close').click(function () {
        $('.shadow,.dialog').remove();
    });
    $('.dialog .yes').click(function () {
        if (type == 1) {
            if (txtchangeAll(1)) {
                $('.shadow,.dialog').remove();
            }
        } else if (type == 2) {
            if (txtchange(currentIndex, 1)) {
                if (editorInstance) {
                    editorInstance.remove();
                }
				for(var i=0;i<editors.length;i++){
					if(editors[i]){
						editors[i].remove();
					}
				}
                if (editorInstance2) {
                    editorInstance2.remove();
                }
				if (editorInstance3) {
                    editorInstance3.remove();
                }
                $('.shadow,.dialog').remove();


            }
        }
    });
    $(window).resize(function () { diaPos('.dialog', '.shadow', diaW); });
}

//弹出框位置控制
function diaPos(dialog, shadow, diaW) {
    var winWidth = $(window).width();
    var winHeight = $(window).height();
    var diaH = $(dialog).height() / 2;
	diaH = 235
    var diaTop = $(window).scrollTop() + (winHeight / 2 - diaH);
    var ml = -diaW / 2;
    $(dialog).css({ top: diaTop + "px", marginLeft: ml + "px", width: diaW + "px"});
    $(shadow).css({ width: winWidth, height: winHeight });
}

