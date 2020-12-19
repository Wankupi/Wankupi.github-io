// 拉取 json 以获取文章列表和友链列表
function getArticle(Arts) {
    let make_html = "";
    for (let i = 0; i < Arts.length && i < 9; ++i)
        make_html += `<div class="card"><h3 class="art-title"><a href="/Article/${Arts[i].path}" target="_blank">${Arts[i].title}</a></h3><div class="art-outline">${Arts[i].outline}</div></div>\n`;
    if (Arts.length > 9)
        make_html += `<div class="card more-art"><h3 class="art-title"><a href="/Article" target="_blank">查看全部文章</a></h3></div>`
    $("#articles").html(make_html);
    if (MathJax.typesetPromise) MathJax.typesetPromise(); else MathJax.startup.typeset = true;
}

function getFriendLinks(Friends) {
    let make_html = "<h3>友链</h3>\n";
    for (let i = 0; i < Friends.length; ++i)
        make_html += `<div class="FriendLink"><a href="${Friends[i].href}" target="_blank" rel="noopener noreferrer">${Friends[i].Name}</a></div>\n`;
    $("#FriendLinkBlock").html(make_html);
}

fetch("/Article/list.json").then(response => response.json()).then(getArticle);
fetch("/static/json/FriendLinks.json").then(response => response.json()).then(getFriendLinks);

// 一言
function getHitokoto() {
    fetch("https://v1.hitokoto.cn?c=i").then(function (response) { return response.json(); })
        .then(function (myJson) {
            $("#hitokoto>i").html(myJson.hitokoto);
            $("#hitokotoWho").text(myJson.from_who);
        });
}
getHitokoto();
$("#hitokoto img").on("click", getHitokoto);

var Top_Panel = $("#top-panel")[0];
document.addEventListener("scroll", function (event) {
    let height = document.documentElement.clientHeight;
    let H = document.documentElement.scrollTop;
    if (H >= height) Top_Panel.style.transform = "translateY(0rem)";
    else Top_Panel.style.transform = "";
});

$(".scroll-down").on("click", function () { $("html,body").animate({ scrollTop: $("main").offset().top }, 1000); });
$("#top-title").on("click", e => { $("html,body").animate({ scrollTop: 0 }, 1000); });