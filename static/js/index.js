(function () {
  function $(s) { return document.querySelector(s); }

  // 拉取 json 以获取文章列表和友链列表
  function putArticleHtml(Arts) {
    function DateToHTML(d) {
      if ((typeof d) != "string") return "";
      let t = new Date(d);
      return `${t.getFullYear()}-${(t.getMonth() + 1).toString().padStart(2, '0')}-${t.getDate().toString().padStart(2, '0')} ` +
        `${t.getHours().toString().padStart(2, "0")}:${t.getMinutes().toString().padStart(2, "0")}`;
    }

    let art_html = "";
    for (let i = 1; i < Arts.length && i <= 9; ++i) {
      let art = Arts[Arts.length - i];
      art.type = art.path.split("/")[0];
      art_html += `<div class="card">` +
        `<h3 class="art-title"><a href="/Article/${art.path}">${art.title}</a></h3>` +
        `<header class="art-meta">` + (
          `<span class="art-type">${art.type}</span>` +
          `<span class="art-date">${DateToHTML(art.date)}</span>`
        ) + `</header>` +
        `<div class="art-outline">${art.outline}</div>` +
        `</div>`;
    }
    if (Arts.length > 9)
      art_html += `<div class="card more-art"><h3 class="art-title"><a href="/Article" target="_blank">更多</a></h3></div>`
    $("#articles").innerHTML = art_html;
    if (MathJax.typesetPromise) MathJax.typesetPromise(); else MathJax.startup.typeset = true;
  }

  fetch("/Article/list.json").then(response => response.json()).then(putArticleHtml);

  // 一言
  function putHitokoto() {
    fetch("https://v1.hitokoto.cn?c=i").then(response => response.json())
      .then(function (myJson) {
        $("#hitokotoText").innerText = myJson.hitokoto;
        $("#hitokotoWho").innerText = myJson.from_who;
      });
  }
  putHitokoto();
  $("#hitokoto img").addEventListener("click", putHitokoto);

  var Top_Panel = $("#top-panel");
  document.addEventListener("scroll", function (event) {
    let height = document.documentElement.clientHeight;
    let H = document.documentElement.scrollTop;
    if (H >= height) Top_Panel.classList.add("show");
    else Top_Panel.classList.remove("show");
  });
})()