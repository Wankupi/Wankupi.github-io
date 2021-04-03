// 拉取 json 以获取文章列表和友链列表
function putArticleHtml(Arts) {
  let art_html = "";
  for (let i = 1; i < Arts.length && i <= 9; ++i) {
    let art = Arts[Arts.length - i];
    art_html += `<div class="card">` +
      `<h3 class="art-title"><a href="/Article/${art.path}" target="_blank">${art.title}</a></h3>` +
      `<div class="art-outline">${art.outline}</div>` +
      `</div>\n`;
  }
  if (Arts.length > 9)
    art_html += `<div class="card more-art"><h3 class="art-title"><a href="/Article" target="_blank">更多</a></h3></div>`
  $("#articles").html(art_html);
  if (MathJax.typesetPromise) MathJax.typesetPromise(); else MathJax.startup.typeset = true;
}

fetch("/Article/list.json").then(response => response.json()).then(putArticleHtml);

// 一言
function putHitokoto() {
  fetch("https://v1.hitokoto.cn?c=i").then(response => response.json())
    .then(function (myJson) {
      $("#hitokotoText").html(myJson.hitokoto);
      $("#hitokotoWho").text(myJson.from_who);
    });
}
putHitokoto();
$("#hitokoto img").on("click", putHitokoto);

var Top_Panel = $("#top-panel")[0];
document.addEventListener("scroll", function (event) {
  let height = document.documentElement.clientHeight;
  let H = document.documentElement.scrollTop;
  if (H >= height) Top_Panel.classList.add("show");
  else Top_Panel.classList.remove("show");
});

$(".scroll-down").on("click", function () { $("html,body").animate({ scrollTop: $("main").offset().top }, 1000); });
$(".back-top").on("click", e => { $("html,body").animate({ scrollTop: 0 }, 1000); });