/* 
 * Natoga V3 controls
 * Requires JQuery >= 1.7.2
 */

/*
 * Handle Loading-Bar Animations
 */
function _n3_animLoadBars(obj) {
    if(obj != null)
        $(".-n3-loading").each(function(){
            $(this).css({backgroundPosition:"0px 0px"});
            $(this).animate({backgroundPosition:"-6500px 0px"}, {duration:((($(this).height() / 35) * 200000) + 60000),queue:false,ease:"linear"}, "linear", function(){_n3_animLoadBars(this)});
        });
    else
        $(obj).animate({backgroundPosition:"-6500px 0px"}, {duration:((($(obj).height() / 35) * 200000) + 60000),queue:false,ease:"linear"}, "linear", function(){_n3_animLoadBars(obj)});
}
$(document).ready(_n3_animLoadBars);

/*
 * Handle fade-in ease-classes
 */
function _n3_fadein_easeclass() {
    $(".-n3-fadein").each(function(){
       $(this).css({opacity:0,visibility:"visible"})
       .animate({opacity:1}, {duration:1000});
    });
    $(".-n3-fadein-1").each(function(){
       $(this).css({opacity:0,visibility:"visible"})
       .animate({opacity:1}, {duration:1000});
    });
    $(".-n3-fadein-2").each(function(){
       $(this).css({opacity:0,visibility:"visible"})
       .delay(300)
       .animate({opacity:1}, {duration:1000});
    });
    $(".-n3-fadein-3").each(function(){
       $(this).css({opacity:0,visibility:"visible"})
       .delay(600)
       .animate({opacity:1}, {duration:1000});
    });
    $(".-n3-fadein-4").each(function(){
       $(this).css({opacity:0,visibility:"visible"})
       .delay(900)
       .animate({opacity:1}, {duration:1000});
    });
    $(".-n3-fadein-5").each(function(){
       $(this).css({opacity:0,visibility:"visible"})
       .delay(1200)
       .animate({opacity:1}, {duration:1000});
    });
}
$(document).ready(_n3_fadein_easeclass);