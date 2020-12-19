// 拉取 json 以获取文章列表和友链列表
function getArticle(Arts) {
  let make_html = "";
  for (let i = 1; i < Arts.length && i <= 9; ++i) {
    let art = Arts[Arts.length - i];
    make_html += `<div class="card"><h3 class="art-title"><a href="/Article/${art.path}" target="_blank">${art.title}</a></h3><div class="art-outline">${art.outline || ""}</div></div>\n`;
  }
  if (Arts.length > 9)
    make_html += `<div class="card more-art"><h3 class="art-title"><a href="/Article" target="_blank">更多</a></h3></div>`
  $("#articles").html(make_html);
  if (MathJax.typesetPromise) MathJax.typesetPromise(); else MathJax.startup.typeset = true;
}

fetch("/Article/list.json").then(response => response.json()).then(getArticle);

// 一言
function getHitokoto() {
  fetch("https://v1.hitokoto.cn?c=i").then(response => response.json())
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
$(".back-top").on("click", e => { $("html,body").animate({ scrollTop: 0 }, 1000); });